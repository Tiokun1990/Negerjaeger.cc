


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																												//			
//											NEGERJAEGER DEV TIOKUN												//
//											NEGERJAEGER DEV JAZZFREE											//
//																												//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//------------------------------------Includes---------------------------------------------------------------------

#include <chrono>
#include <ctime>
#include <stdint.h>
#include <Shlobj.h>

#include "Client.h"
#include "../ImGui/imgui.h"
#include "../ConfigPop/cfgmsgpop.h"
#include "../Cheat/GrenadeHelper/CGrenadeAPI.h"
#include "../Cheat/Ragebot/Ragebot.h"


//[enc_string_enable /]
//[junk_enable /]


//-------------------------------Client------------------------------------------------------------------------------
namespace Client
{
	string BaseDir = "C:\\Negerjaeger.cc";
	string LogFile = "";
	string GuiFile = "";
	string IniFile = "";

	int	iScreenWidth = 0;
	int	iScreenHeight = 0;

	char* username = getenv("USERPROFILE");

	vector<string> ConfigList;

	Vector2D	g_vCenterScreen = Vector2D(0.f, 0.f);


	CKnifebot*	g_pKnifebot = nullptr;
	CResolver*  g_pResolver = nullptr;
	CFakeLag*   g_pFakeLag = nullptr;
	CAntiAim*   g_pAntiAim = nullptr;
	CPlayers*	g_pPlayers = nullptr;
	CRender*	g_pRender = nullptr;
	CAimbot*	g_pAimbot = nullptr;
	CRadar*		g_pRadar = nullptr;
	CSkin*		g_pSkin = nullptr;
	CMisc*		g_pMisc = nullptr;
	CGui*		g_pGui = nullptr;
	CEsp*		g_pEsp = nullptr;

	CInventoryChanger1* g_pInventoryChanger1 = nullptr;
	CInventoryChanger* g_pInventoryChanger = nullptr;



	bool		bC4Timer = false;
	int			iC4Timer = 40;

	int			iWeaponSelectIndex = WEAPON_DEAGLE;
	int			iWeaponSelectSkinIndex = -1;
	int			iWeaponID = 0;



	//---------------------------------ConigSettings-----------------------------------------------------------------------------------

	void ReadConfigs(LPCTSTR lpszFileName)
	{
		if (!strstr(lpszFileName, "gui.ini"))
		{
			ConfigList.push_back(lpszFileName);
		}
	}
	void RefreshConfigs()
	{
		ConfigList.clear();
		string ConfigDir = "C:/Negerjaeger.cc/*.ini";
		CreateDirectoryW(L"C:\\Negerjaeger.cc", NULL);
		GuiFile = "C:/Negerjaeger.cc/gui.ini";
		SearchFiles(ConfigDir.c_str(), ReadConfigs, FALSE);
	}



	//--------------------------------------InitializeClient----------------------------------------------------------------


	bool Initialize(IDirect3DDevice9* pDevice)
	{


		g_pRender = new CRender(pDevice);
		g_pKnifebot = new CKnifebot();
		g_pResolver = new CResolver();
		g_pAntiAim = new CAntiAim();
		g_pFakeLag = new CFakeLag();
		g_pPlayers = new CPlayers();
		g_pAimbot = new CAimbot();
		g_pRadar = new CRadar();
		g_pSkin = new CSkin();
		g_pMisc = new CMisc();
		g_pGui = new CGui();
		g_pEsp = new CEsp();

		g_pInventoryChanger = new CInventoryChanger();


		//-------------------------ConfigSettings-------------------------------------------------------------------------------

		GuiFile = "C:/Negerjaeger.cc/gui.ini";
		IniFile = "C:/Negerjaeger.cc/settings.ini";

		g_pSkin->InitalizeSkins();

		Settings::LoadSettings(IniFile);

		iWeaponSelectSkinIndex = GetWeaponSkinIndexFromPaintKit(g_SkinChangerCfg[iWeaponSelectIndex].nFallbackPaintKit);

		g_pGui->GUI_Init(pDevice);

		RefreshConfigs();

		return true;
	}

	//--------------------------------Shutdown-------------------------------------------------------------------------------

	void Shutdown()
	{

		DELETE_MOD(g_pKnifebot);
		DELETE_MOD(g_pResolver);
		DELETE_MOD(g_pFakeLag);
		DELETE_MOD(g_pAntiAim);
		DELETE_MOD(g_pPlayers);
		DELETE_MOD(g_pAimbot);
		DELETE_MOD(g_pRender);
		DELETE_MOD(g_pRadar);
		DELETE_MOD(g_pSkin);
		DELETE_MOD(g_pMisc);
		DELETE_MOD(g_pGui);
		DELETE_MOD(g_pEsp);
	}


	//------------------------------FPSCOUNTER--------------------------------------------------------------------------------

	int get_fps()
	{
		using namespace std::chrono;
		static int count = 0;
		static auto last = high_resolution_clock::now();
		auto now = high_resolution_clock::now();
		static int fps = 0;

		count++;

		if (duration_cast<milliseconds>(now - last).count() > 1000)
		{
			fps = count;
			count = 0;
			last = now;
		}
		return fps;
	}


	//-----------------------------------OnRender-----------------------------------------------------------------------------------

	void OnRender()
	{
		if (g_pRender && !Interfaces::Engine()->IsTakingScreenshot() && Interfaces::Engine()->IsActiveApp())
		if (g_pRender && Interfaces::Engine()->IsActiveApp())
		{
			g_pRender->BeginRender();

			if (g_pGui)
				g_pGui->GUI_Draw_Elements();

			Interfaces::Engine()->GetScreenSize(iScreenWidth, iScreenHeight);

			g_vCenterScreen.x = iScreenWidth / 2.f;
			g_vCenterScreen.y = iScreenHeight / 2.f;

			{
				if (g_pEsp)
					g_pEsp->OnRender();

				if (g_pMisc)
				{
					g_pMisc->OnRender();
					g_pMisc->OnRenderSpectatorList();
				}
			}

			std::time_t result = std::time(nullptr);



			g_pRender->EndRender();
		}
	}


	void OnLostDevice()
	{
		if (g_pRender)
			g_pRender->OnLostDevice();

		if (g_pGui)
			ImGui_ImplDX9_InvalidateDeviceObjects();
	}

	void OnResetDevice()
	{
		if (g_pRender)
			g_pRender->OnResetDevice();

		if (g_pGui)
			ImGui_ImplDX9_CreateDeviceObjects();
	}

	//--------------------------------Inventorychanger-------------------------------------------------------------------------------


	void OnRetrieveMessage(void* ecx, void* edx, uint32_t *punMsgType, void *pubDest, uint32_t cubDest, uint32_t *pcubMsgSize)
	{
		g_pInventoryChanger->PostRetrieveMessage(punMsgType, pubDest, cubDest, pcubMsgSize);
	}

	void OnSendMessage(void* ecx, void* edx, uint32_t unMsgType, const void* pubData, uint32_t cubData)
	{

		void* pubDataMutable = const_cast<void*>(pubData);
		g_pInventoryChanger->PreSendMessage(unMsgType, pubDataMutable, cubData);
	}

	//-----------------------------CreateMove------------------------------------------------------------------------------------------


	void OnCreateMove(CUserCmd* cmd)
	{
		if (g_pPlayers && Interfaces::Engine()->IsInGame())
		{
			g_pPlayers->Update();

			if (g_pEsp)
				g_pEsp->OnCreateMove(cmd);

			if (IsLocalAlive())
			{
				if (!bIsGuiVisible)
				{
					int iWeaponSettingsSelectID = GetWeaponSettingsSelectID();

					if (iWeaponSettingsSelectID >= 0)
						iWeaponID = iWeaponSettingsSelectID;
				}

				if (g_pAimbot)
					g_pAimbot->OnCreateMove(cmd, g_pPlayers->GetLocal());

				if (g_pKnifebot)
					g_pKnifebot->OnCreateMove(cmd);

				if (g_pMisc)
					g_pMisc->OnCreateMove(cmd);

				G::LocalPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
				G::UserCmd = cmd;

				DWORD* framePointer;
				__asm mov framePointer, ebp;
				*(bool*)(*framePointer - 0x1C) = G::SendPacket;

				if (G::SendPacket)
					G::VisualAngle = G::LocalPlayer->GetEyeAngles();


				backtracking->legitBackTrack(cmd);
			}
		}
	}


	//-----------------------------------------FireEvent------------------------------------------------------------------------

	void OnFireEventClientSideThink(IGameEvent* pEvent)
	{
		if (!strcmp(pEvent->GetName(), "player_connect_full") ||
			!strcmp(pEvent->GetName(), "round_start") ||
			!strcmp(pEvent->GetName(), "cs_game_disconnected"))
		{
			if (g_pPlayers)
				g_pPlayers->Clear();

			if (g_pEsp)
				g_pEsp->OnReset();
		}


		if (Interfaces::Engine()->IsConnected())
		{
			hitmarker::singleton()->initialize();

			if (g_pEsp)
				g_pEsp->OnEvents(pEvent);

			if (g_pAimbot)
				g_pAimbot->OnEvents(pEvent);

			if (g_pSkin)
				g_pSkin->OnEvents(pEvent);

			if (g_pMisc)
				g_pMisc->OnEvents(pEvent);
		}
	}


	//-----------------------------Framestage-------------------------------------------------------------------------


	void OnFrameStageNotify(ClientFrameStage_t Stage)
	{
		if (Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected())
		{
			Skin_OnFrameStageNotify(Stage);
			Gloves_OnFrameStageNotify(Stage);
		}
	}

	//---------------------------------Model----------------------------------------------------------------------------------


	void OnDrawModelExecute(IMatRenderContext* ctx, const DrawModelState_t &state,
		const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld)
	{
		if (Interfaces::Engine()->IsInGame() && ctx && pCustomBoneToWorld)
		{
			if (g_pEsp)
				g_pEsp->OnDrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);

			if (g_pMisc)
				g_pMisc->OnDrawModelExecute();
		}
	}


	//--------------------------------View-------------------------------------------------------------------------------

	void OnOverrideView(CViewSetup* pSetup)
	{
		if (g_pMisc)
			g_pMisc->OnOverrideView(pSetup);
	}

	void OnGetViewModelFOV(float& fov)
	{
		if (g_pMisc)
			g_pMisc->OnGetViewModelFOV(fov);
	}

	BOOL DirectoryExists(LPCTSTR szPath)
	{
		DWORD dwAttrib = GetFileAttributes(szPath);

		return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
			(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}


	//----------------------------------------Rainbowclient----------------------------------------------------------------------------------------

	void ImDrawRectRainbow(int x, int y, int width, int height, float flSpeed, float &flRainbow)
	{
		ImDrawList* windowDrawList = ImGui::GetWindowDrawList();

		Color colColor(0, 0, 0, 255);

		flRainbow += flSpeed;
		if (flRainbow > 1.f) flRainbow = 0.f;//1 0 

		for (int i = 0; i < width; i = i + 1)
		{
			float hue = (1.f / (float)width) * i;
			hue -= flRainbow;
			if (hue < 0.f) hue += 1.f;

			Color colRainbow = colColor.FromHSB(hue, 1.f, 1.f);
			windowDrawList->AddRectFilled(ImVec2(x + i, y), ImVec2(width, height), colRainbow.GetU32());
		}
	}


	//-----------------------------------------------------RenderGui---------------------------------------------------------------------------------------------

	void OnRenderGUI()
	{
		static int tabSelected = 0;
		ImVec2 mainWindowPos;

		ImGui::SetNextWindowSize(ImVec2(930, 730)); // format = width height
		g_pGui->NameFont();
		if (ImGui::Begin("Negerjaeger.cc", &bIsGuiVisible, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
			g_pRender->DrawFillBox(0, 0, iScreenWidth, iScreenHeight, Color(0, 0, 0, 170));
		{
			
			mainWindowPos = ImGui::GetWindowPos();

			//---------------------Raimbow-----------------------------------------------------------------------------------

			static float flRainbow;
			static float flSpeed = 0.003;
			int curWidth = 3;
			ImVec2 curPos = ImGui::GetCursorPos();
			ImVec2 curWindowPos = ImGui::GetWindowPos();
			curPos.x += curWindowPos.x;
			curPos.y += curWindowPos.y;
			int size = 2;
			int y;
			Interfaces::Engine()->GetScreenSize(y, size);
			ImDrawRectRainbow(curPos.x - 10, curPos.y - 1, ImGui::GetWindowSize().x + size, curPos.y + -4, flSpeed, flRainbow);

			//---------------------------Groups--------------------------------------------------------------------------------------------------

			ImGui::BeginGroup();

			if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_FovType > 1)
				Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_FovType = 1;

			if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_BestHit > 1)
				Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_BestHit = 1;

			if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Spot > 5)
				Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Spot = 5;

			enum DWRITE_READING_DIRECTION {
				DWRITE_READING_DIRECTION_LEFT_TO_RIGHT,
				DWRITE_READING_DIRECTION_RIGHT_TO_LEFT
			};

			g_pGui->bluefont();
			ImGui::TextColored(ImVec4{ 0.0f, 0.5f, 0.0f, 1.0f }, "FPS:%03d", get_fps());
			ImGui::Separator();
			g_pGui->IconFont();
			const char* tabNames[] = {
				"A" ,"I" , "B" , "G" };

			static int tabOrder[] = { 0 , 1 , 2 , 3 };
			static int tabSelected = 5;
			const bool tabChanged = ImGui::TabLabels(tabNames,
				sizeof(tabNames) / sizeof(tabNames[0]),
				tabSelected, tabOrder);

			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();

			static int iConfigSelect = 0;
			static int iMenuSheme = 1;
			static char ConfigName[64] = { 0 };

			//-------------------------------------------Configs-------------------------------------------------------------------------

			g_pGui->bluefont();
			ImGui::PushItemWidth(100.f);
			ImGui::ComboBoxArray("##1", &iConfigSelect, ConfigList);
			ImGui::Spacing();
			ImGui::PushItemWidth(100.f);
			ImGui::InputText("##0", ConfigName, 64);
			if (ImGui::Button("Create", ImVec2(100.f, 25.f)))
			{
				string ConfigFileName = ConfigName;

				if (ConfigFileName.size() < 1)
				{
					ConfigFileName = "settings";
				}

				Settings::SaveSettings("C:/Negerjaeger.cc/" + ConfigFileName + ".ini");
				RefreshConfigs();
			}
			ImGui::Spacing();
			if (ImGui::Button("Load", ImVec2(47.5f, 25.f)))
			{
				Settings::LoadSettings("C:/Negerjaeger.cc/" + ConfigList[iConfigSelect]);
			}
			ImGui::SameLine();
			if (ImGui::Button("Save", ImVec2(47.5f, 25.f)))
			{
				Settings::SaveSettings("C:/Negerjaeger.cc/" + ConfigList[iConfigSelect]);

			}
			ImGui::Spacing();
			if (ImGui::Button("Refresh", ImVec2(100.f, 25.f)))
			{
				RefreshConfigs();
			}




			//-------------------------------------------SpaceLines-----------------------------------------------------------------------------

			ImGui::Separator();

			ImGui::Columns();

			float SpaceLineTitleOne = 120.f;
			float SpaceLineTitleTwo = 230.f;
			float SpaceLineTitleThr = 460.f;
			float SpaceLineTitleFour = 460.f;


			float SpaceLineBoxOne = 135.f;
			float SpaceLineBoxTwo = 275.f;
			float SpaceLineBoxThr = 410.f;
			float SpaceLineBoxFour = 475.f;


			float SpaceLineOne = 120.f;
			float SpaceLineTwo = 240.f;
			float SpaceLineThr = 360.f;
			float SpaceLineFour = 440.f;

			const char* weapons[33] =
			{
				"deagle",
				"elite",
				"fiveseven",
				"glock18",
				"p2000",
				"p250",
				"usp_s",
				"cz75",
				"revolver",
				"tec9",
				"ak47",
				"aug",
				"famas",
				"galilar",
				"m249",
				"m4a4",
				"m4a1_s",
				"mac10",
				"p90",
				"ump45",
				"xm1014",
				"bizon",
				"mag7",
				"negev",
				"sawedoff",
				"mp7",
				"mp9",
				"nova",
				"sg553",
				"scar20",
				"g3sg1",
				"awp",
				"ssg08"
			};

			ImGui::EndGroup();
			ImGui::SameLine();

			//---------------------------------------------------------------------------------Ragebot--------------------------------------------------------------------------------------------
			if (tabSelected == 0) // Aimbot
				{
				g_pGui->bluefont();


				static int otherpages = 1;
				const char* ClampType[] = { "All Target" , "Shot" , "Shot + Target" };
				const char* Aimspot[] = { "Head" , "Neck" ,  "Body" , "Thorax" , "Chest" };
				const char* AimFovType[] = { "Dynamic" , "Static" };
				const char* BestHit[] = { "Disable" , "Enable" };

				ImGui::BeginGroup();
				ImGui::BeginChild(1, ImVec2(-1, 680), true);
				{

					ImGui::BeginGroup();

					ImGui::Text("LEGITBOT");
					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();

					ImGui::Combo("Weapon", &iWeaponID, pWeaponData, IM_ARRAYSIZE(pWeaponData));
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Select the Weapon you wan't to change the config for");


					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();

					ImGui::Checkbox("Active", &Settings::Aimbot::aim_Active);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Master Switch");
					ImGui::SameLine();
					ImGui::Checkbox("On Key", &Settings::Aimbot::aim_OnKey);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Enables Aimbot on Key");
					ImGui::SameLine();
					if (Settings::Aimbot::aim_OnKey)
						ImGui::Hotkey("Key", &Settings::Aimbot::aim_Key, ImVec2(100, 25));
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Press Key for Aimbot Toggle");

					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();



					ImGui::Checkbox("Attack Team", &Settings::Aimbot::aim_Deathmatch);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Useful in free for all community servers");
					ImGui::SameLine(SpaceLineOne);
					ImGui::Checkbox("Trough Walls", &Settings::Aimbot::aim_WallAttack);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("activates aimbot if player takes damage through penetrable walls");
					ImGui::SameLine(SpaceLineTwo);
					ImGui::Checkbox("Smoke Check", &Settings::Aimbot::aim_CheckSmoke);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("does not activate aimbot if smoke is between you and the enemy");

					ImGui::Checkbox("Jump Check", &Settings::Aimbot::aim_AntiJump);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Disables aimbot if enemy and/or you are jumping");
					ImGui::SameLine(SpaceLineOne);
					ImGui::Checkbox("Flash Check", &Settings::Aimbot::aim_CheckFlash);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Disables aimbot if you are Flashed");
					ImGui::SameLine(SpaceLineTwo);
					ImGui::Checkbox("Fast Zoom", &Settings::Aimbot::aim_FastZoom);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Fastzoom for AWP/Sout/Auto");


					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();


					ImGui::Checkbox("Draw Fov", &Settings::Aimbot::aim_DrawFov);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Renders radius of influence of aimbot");
					ImGui::SameLine(SpaceLineOne);
					ImGui::Checkbox("Draw Aim-Spot", &Settings::Aimbot::aim_DrawSpot);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Renders point of aimbot attack");
					ImGui::SameLine(SpaceLineTwo);
					ImGui::Checkbox("Auto Crouch", &Settings::Aimbot::aim_Crouch);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Auto Crouchs if you shoot for higher Accuracy");




					ImGui::Checkbox("Draw Recoil", &Settings::Misc::misc_Punch2);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Draws Recoil");
					ImGui::SameLine(SpaceLineOne);
					ImGui::Checkbox("Draw Spread", &Settings::Misc::ShowSpread);			//Disabled (Update Framestage)
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Draws Spread as Circle - Enable Barre Radar or it doesnt work");

					
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("Auto Pistol", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("ability to use pistols like an automatic gun, hold down left mouse button");
					

					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();

					ImGui::Checkbox("Backtrack", &Settings::Aimbot::aim_Backtrack);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("You can teleport enemies to an older position and kill them");
					ImGui::SameLine(SpaceLineOne);
					ImGui::Checkbox("Visualise Ticks", &Settings::Aimbot::aim_DrawBacktrack);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Renders Ticks with potential to be Backtracked");
					ImGui::SliderInt("Tickrate", &Settings::Aimbot::aim_Backtracktickrate, 1, 12);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Set Backtrack Tick Tate (higher number longer backtrack)");

					ImGui::Spacing();
				
					ImGui::Separator();
					ImGui::Spacing();
					ImGui::Spacing();

					if (ImGui::Button("Aimbot", ImVec2(395.5f, 20.0f))) // <---- customize these to your liking.
					{
						otherpages = 1;
					}
					ImGui::SameLine();
					if (ImGui::Button("Recoil", ImVec2(395.5f, 20.0f))) // <---- again, customize to your liking.
					{
						otherpages = 2;
					}

					if (otherpages == 1)
					{
						ImGui::Spacing();
						ImGui::Separator();

						ImGui::Spacing();

						if (ImGui::Checkbox("pSilent", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_pSilent))
						
						{
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Smooth = 1;
						}


						ImGui::SameLine();
						ImGui::SliderInt("pSilent Fov", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_pSilentFov, 1, 180);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Sets FOV for Silent Aimbot - Silent Aimbot Shoots at Targets without Aiming at them - OBVIOUS IN OVERWATCH!");

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();


						ImGui::Text("Aimbot Settings");
						ImGui::SliderInt("Aimbot Fov", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Fov, 1, 180);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("area that aimbot effects");
						ImGui::Spacing();
					
						ImGui::SliderInt("Smoothing", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Smooth, 1, 300);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("humanizes aimbot's travel to enemy - lower fov = snapping - higher fov = looks real");
						ImGui::SliderInt("Ultrasmooth", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Smooth, 1, 3000);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("You can change the smoothing up to 3000 - Extreme Smooth Aimbot");
						ImGui::Spacing();

						ImGui::Combo("Fov Type", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_FovType, AimFovType, IM_ARRAYSIZE(AimFovType));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("dynamic changes size of FOV depending on distance between you and enemy");

						ImGui::Combo("Best Hit", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_BestHit, BestHit, IM_ARRAYSIZE(BestHit));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Looks more legit, rather than forcing hitting aimspot every time");

						ImGui::Combo("Aimspot", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Spot, Aimspot, IM_ARRAYSIZE(Aimspot));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("if besthit is disabled, this forces one location for the aimbot to travel to");


						if (ImGui::SliderFloat("KillDelay", &Settings::Aimbot::aim_KillDelayTime, 0.f, 2.f))
						{
							Settings::Aimbot::aim_KillDelay = 1;
						}
						ImGui::SliderInt("ShotDelay", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Delay, 1, 200);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("amount of time before automated rcs kicks in");

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Text("Custom Settings - Auto Adjust your Smoothness");



						if (ImGui::Button("Rage - No Smooth"))
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Smooth = 0,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsSmooth = 0,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsx = 100,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsy = 100,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Fov = 180,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsFov = 180,
							Settings::Aimbot::aim_Backtrack = true,
							Settings::Aimbot::aim_DrawBacktrack = true,
							Settings::Aimbot::aim_Backtracktickrate = 12,
							Settings::Aimbot::aim_WallAttack = true;
						ImGui::SameLine(SpaceLineTwo);

						if (ImGui::Button("Obvious - Barely Smooth"))
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Smooth = 200,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsSmooth = 100,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsx = 100,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsy = 100,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Fov = 120,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsFov = 70,
							Settings::Aimbot::aim_Backtrack = true,
							Settings::Aimbot::aim_DrawBacktrack = true,
							Settings::Aimbot::aim_Backtracktickrate = 10,
							Settings::Aimbot::aim_WallAttack = true;
						ImGui::SameLine(SpaceLineFour);



						if (ImGui::Button("Human - Great Smooth"))
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Smooth = 700,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsSmooth = 250,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsx = 100,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsy = 100,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Fov = 65,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsFov = 25,
							Settings::Aimbot::aim_CheckSmoke = true,
							Settings::Aimbot::aim_CheckFlash = true,
							Settings::Aimbot::aim_Backtrack = true,
							Settings::Aimbot::aim_DrawBacktrack = true,
							Settings::Aimbot::aim_Backtracktickrate = 4;

						if (ImGui::Button("Totally Obvious - Almost no smooth"))
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Smooth = 50,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsSmooth = 40,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsx = 95,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsy = 94,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Fov = 150,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsFov = 150,
							Settings::Aimbot::aim_Backtrack = true,
							Settings::Aimbot::aim_DrawBacktrack = true,
							Settings::Aimbot::aim_Backtracktickrate = 12,
							Settings::Aimbot::aim_WallAttack = true;
						ImGui::SameLine(SpaceLineTwo);


						if (ImGui::Button("Unhuman - Average Smooth"))
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Smooth = 350,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsSmooth = 200,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsx = 100,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsy = 100,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Fov = 90,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsFov = 45,
							Settings::Aimbot::aim_CheckSmoke = true,
							Settings::Aimbot::aim_CheckFlash = true,
							Settings::Aimbot::aim_Backtrack = true,
							Settings::Aimbot::aim_DrawBacktrack = true,
							Settings::Aimbot::aim_Backtracktickrate = 8;
						ImGui::SameLine(SpaceLineFour);

						if (ImGui::Button("Overlegit - Ultra Smooth"))
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Smooth = 1000,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsSmooth = 350,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsx = 100,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsy = 100,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Fov = 40,
							Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsFov = 10,
							Settings::Aimbot::aim_CheckSmoke = true,
							Settings::Aimbot::aim_CheckFlash = true,
							Settings::Aimbot::aim_AntiJump = true;



					}
					if (otherpages == 2)
					{

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						
						ImGui::Combo("RCS Clamp", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsClampType, ClampType, IM_ARRAYSIZE(ClampType));


						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::SliderInt("RCS Amounth X", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsx, 1, 100);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Reduces the Recoil - Left and Right");
						ImGui::SliderInt("RCS Amounth Y", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsy, 1, 100);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Reduces the Recoil - Up and Down");
						ImGui::SliderInt("RCS Fov", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsFov, 1, 180);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Anti Recoil Amount - High Fov = Low Recoil");
						ImGui::Spacing();

						ImGui::SliderInt("RCS Smooth", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsSmooth, 1, 360);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Smooths your Anti Recoil - High Amount = Legit Anti Recoil");
						ImGui::SliderInt("RCS UltraSmooth", &Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsSmooth, 1, 3000);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Ultra Smoothnes - Change it up to 3000 for Extreme Smooth Aimbot");
					}



				}

				ImGui::EndChild();
				ImGui::EndGroup();
				//------------------------------------------------------------------------------Visuals-----------------------------------------------------------------------
			}
			else if (tabSelected == 1) // Visuals
			{

				g_pGui->bluefont();
				ImGui::BeginGroup();
				ImGui::BeginChild(1, ImVec2(-1, 680), true);
				{
					const char* iHitSound[] =
					{
						"Off",
						"Default",
						"Anime",
						"Roblox",
						"GameSense",
						"German",
						"HeadMeme",
						"FadeCSGO.tk"
					};

					const char* material_items[] =
					{
						"glass",
						"crystal",
						"dark gold",
						"dark chrome",
						"plastic glass",
						"velvet",
						"crystal blue",
						"bright gold"
					};


					string style_1 = "None";
					string style_2 = "Box";
					string style_3 = "Corner Box";
					string style_4 = "Half box";
					const char* items1[] = { style_1.c_str() , style_2.c_str() , style_3.c_str(), style_4.c_str() };

					const char* armtype_items[] =
					{
						"arms only",
						"arms and weapon"
					};

					const char* skybox_items[] =
					{
						"cs_baggage_skybox_",
						"cs_tibet",
						"embassy",
						"italy",
						"jungle",
						"nukeblank",
						"office",
						"sky_cs15_daylight01_hdr",
						"sky_cs15_daylight02_hdr",
						"sky_cs15_daylight03_hdr",
						"sky_cs15_daylight04_hdr",
						"sky_csgo_cloudy01",
						"sky_csgo_night02",
						"sky_csgo_night02b",
						"sky_csgo_night_flat",
						"sky_day02_05_hdr",
						"sky_day02_05",
						"sky_dust",
						"sky_l4d_rural02_ldr",
						"sky_venice",
						"vertigo_hdr",
						"vertigoblue_hdr",
						"vertigo",
						"vietnam"
					};

					ImGui::Text("ESP");
					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();



					static int otherpages = 0;



					if (ImGui::Button("Esp", ImVec2(260.0f, 30.0f))) // <---- customize these to your liking.
					{
						otherpages = 0;
					}
					ImGui::SameLine();

					if (ImGui::Button("Misc. visuals", ImVec2(260.0f, 30.0f))) // <---- again, customize to your liking.
					{
						otherpages = 1;
					}
					ImGui::SameLine();
					if (ImGui::Button("Radar", ImVec2(260.0f, 30.0f))) // <---- again, customize to your liking.
					{
						otherpages = 2;
					}



					if (otherpages == 0)
					{
						static int otherpages = 0;



						if (ImGui::Button("Visuals", ImVec2(126.0f, 25.0f))) // <---- customize these to your liking.
						{
							otherpages = 0;
						}
						ImGui::SameLine();
						if (ImGui::Button("Options", ImVec2(126.0f, 25.0f))) // <---- again, customize to your liking.
						{
							otherpages = 1;
						}

						ImGui::Separator();

						if (otherpages == 0)
						{



							ImGui::PushItemWidth(339.f);
							ImGui::Combo("Esp Type", &Settings::Esp::esp_Style, items1, IM_ARRAYSIZE(items1));
							ImGui::PopItemWidth();


							ImGui::Spacing();

							ImGui::BeginGroup();

							ImGui::PushItemWidth(150.f);
							ImGui::BeginChild("first child", ImVec2(135, 120), true);
							{
								ImGui::Checkbox("Team Esp", &Settings::Esp::esp_Team);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("Render Teammates");
								ImGui::Checkbox("Enemy Esp", &Settings::Esp::esp_Enemy);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("Render Enemies");
								ImGui::Checkbox("Skeleton", &Settings::Esp::esp_Skeleton);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("Rendering of bones of enemies");
								ImGui::Checkbox("Outline", &Settings::Esp::esp_Outline);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("Draws black outline over box");

							}
							ImGui::EndChild();
							ImGui::PopItemWidth();
							ImGui::EndGroup();

							ImGui::SameLine(SpaceLineBoxOne);

							ImGui::BeginGroup();
							ImGui::PushItemWidth(300.f);
							ImGui::BeginChild("Second child", ImVec2(200, 120), true);
							{
								ImGui::Checkbox("Name Esp", &Settings::Esp::esp_Name);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("Renders name of players");
								ImGui::Checkbox("Bomb Esp", &Settings::Esp::esp_Bomb);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders position of bomb on players and when planted");
								ImGui::Checkbox("Weapon Esp", &Settings::Esp::esp_Weapon);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders text of current weapon held by enemies");
								ImGui::Checkbox("Ammo esp", &Settings::Esp::esp_Ammo);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("Renders text of amount of ammunition enemy has");
							}
							ImGui::EndChild(); //ends the child
							ImGui::PopItemWidth(); //pops the item width
							ImGui::EndGroup(); //ends the group


							ImGui::SameLine(SpaceLineBoxTwo);

							ImGui::BeginGroup(); //begins the group
							ImGui::PushItemWidth(300.f); //item width
							ImGui::BeginChild("Third Child", ImVec2(145, 120), true); //begins the child and the size of the child.
							{
								ImGui::Checkbox("Reveal Ranks", &Settings::Esp::esp_Rank);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("in scoreboard - buggy");
								
	
								ImGui::Checkbox("Line Esp", &Settings::Esp::esp_Line);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("draws line to enemy");
								ImGui::Checkbox("Distance Esp", &Settings::Esp::esp_Distance);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("renders text for distance between you and enemy");
							}
							ImGui::EndChild(); //ends the child
							ImGui::PopItemWidth(); //pops the item width
							ImGui::EndGroup(); //ends the group

							ImGui::SameLine(SpaceLineBoxThr);

							ImGui::BeginGroup(); //begins the group
							ImGui::PushItemWidth(300.f); //item width
							ImGui::BeginChild("fourth child", ImVec2(1200, 120), true); //begins the child and the size of the child.
							{
								
								
								ImGui::Checkbox("Is Defusing", &Settings::Esp::esp_Defusing);
								{
									if (!Interfaces::Engine()->IsInGame())
										Settings::Esp::esp_Defusing;
								}
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("Draws (Defusing) on Enemies if they Defuse - Disabled in Main Menu (crashfix)");
								ImGui::Checkbox("Is Scoped", &Settings::Esp::esp_InScoped);
								{
									if (!Interfaces::Engine()->IsInGame())
										Settings::Esp::esp_InScoped;
								}
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("Draws (Scoped) on Enemies if they are Scoping - Disabled in Main Menu (crashfix)");
								ImGui::Checkbox("Is Flashed", &Settings::Esp::esp_Flashed);
								{
									if (!Interfaces::Engine()->IsInGame())
										Settings::Esp::esp_Flashed;
								}
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("Draws (Flashed) on Enemies if they are Flashed - Disabled in Main Menu (crashfix)");


							}
							ImGui::EndChild();
							ImGui::PopItemWidth();
							ImGui::EndGroup();


							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();

							ImGui::Checkbox("dropped weapon esp", &Settings::Esp::esp_WorldWeapons);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders text of dropped weapons on them");
							ImGui::SameLine(SpaceLineTwo);
							ImGui::PushItemWidth(250.f);
							ImGui::ColorEdit3("WW Color", Settings::Esp::WorldWeapon_Color);
							ImGui::PopItemWidth();


							
							


							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();

							ImGui::Checkbox("Capslock Boxtoggle", &Settings::Esp::esp_CapitalToggle);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("Disables ESP until you press and hold CAPSLOCK");
							ImGui::SameLine(SpaceLineTwo);
							ImGui::Checkbox("Fish Esp", &Settings::Esp::esp_Fish);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("Displays Fishes");
							ImGui::SameLine(SpaceLineThr);
							ImGui::Checkbox("Chicken Esp", &Settings::Esp::esp_Chicken);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("Displays Chickens");

						

								/*ImGui::Checkbox("Grenade Tracer", &Settings::Esp::esp_GrenadePrediction);
								if (ImGui::IsItemHovered())
									ImGui::SetTooltip("Draws a Line where the nade will hit - Disabled in Menu (crashfix)");
								{
									if (!Interfaces::Engine()->IsInGame())
										Settings::Esp::esp_GrenadePrediction = false;
								}
								*/
							

							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();

							static bool sh_save_cfg = false;

							if (ImGui::Checkbox("Grenade Helper", &Settings::Esp::helper))
								sh_save_cfg = true;
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("buy a smoke, hold it in your hand, walk on a red circle, bottom left screen is info, throw as instructed at the green point - Only works on few maps");
							
							ImGui::SameLine();
							if (ImGui::Button("update map"))
								cGrenade.bUpdateGrenadeInfo(Interfaces::Engine()->GetLevelNameShort());
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("Press this if Grenade Helper doesn't work - Only works on few maps");

							ImGui::SameLine(SpaceLineTwo);
							ImGui::Checkbox("Grenade Boxes", &Settings::Esp::esp_WorldGrenade);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders 3D box around grenades regardless of type");

							




							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();


							ImGui::Checkbox("Asus Walls", &Settings::Esp::esp_AsusWalls);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("Changes Opacity of Walls");
							ImGui::SameLine(SpaceLineOne);
							ImGui::Checkbox("Night Mode", &Settings::Esp::esp_NightMode);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN - Turns everything dark");
							ImGui::SliderInt("Walls Opacity	", &Settings::Esp::esp_WallsOpacity, 0, 100);

							ImGui::ColorEdit3("Ambient Light", Settings::Esp::esp_Ambient);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("SMAC BAN - Changes World Color");
							ImGui::Spacing();
						
						
							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();


							string chams_1 = "None";
							string chams_2 = "Flat";
							string chams_3 = "Texture";
							const char* items5[] = { chams_1.c_str() , chams_2.c_str() , chams_3.c_str() };

							string hpbar_1 = "None";
							string hpbar_2 = "Number";
							string hpbar_3 = "Bottom";
							string hpbar_4 = "Left";
							string hpbar_5 = "Edgy";

							const char* items3[] = { hpbar_1.c_str() , hpbar_2.c_str() , hpbar_3.c_str() , hpbar_4.c_str(), hpbar_5.c_str() };

							string arbar_1 = "None";
							string arbar_2 = "Number";
							string arbar_3 = "Bottom";
							string arbar_4 = "Right";
							string arbar_5 = "Edgy";

							const char* items4[] = { arbar_1.c_str() , arbar_2.c_str() , arbar_3.c_str() , arbar_4.c_str(), arbar_5.c_str() };



							ImGui::Combo("Esp Health", &Settings::Esp::esp_Health, items3, IM_ARRAYSIZE(items3));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders health of players");


							ImGui::Combo("Esp Armor", &Settings::Esp::esp_Armor, items4, IM_ARRAYSIZE(items4));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("renders armor of players");

							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();
							ImGui::Text("Chams Options");
							ImGui::Spacing();

							ImGui::Combo("Chams", &Settings::Esp::esp_Chams, items5, IM_ARRAYSIZE(items5));
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("fills player models with colour");

							ImGui::Checkbox("Chams Wall", &Settings::Esp::esp_ChamsVisible);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("Different Chams color if enemy is behind a Wall");
							ImGui::Checkbox("Health Chams", &Settings::Esp::esp_HealthChams);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("Changes Chams color based on HP - may crashs the game (CPU Heavy)");





						}

						if (otherpages == 1)
						{



						



							


							ImGui::Spacing();

							ImGui::Text("ESP Colours");
							ImGui::Spacing();
							ImGui::PushItemWidth(150.f);
							ImGui::ColorEdit3("Esp CT", Settings::Esp::esp_Color_CT);
							ImGui::SameLine(SpaceLineTwo);
							ImGui::ColorEdit3("Esp Visible CT", Settings::Esp::esp_Color_VCT);

							ImGui::ColorEdit3("Esp T", Settings::Esp::esp_Color_TT);
							ImGui::SameLine(SpaceLineTwo);
							ImGui::ColorEdit3("Esp Visible T", Settings::Esp::esp_Color_VTT);
							ImGui::PopItemWidth();

							ImGui::Spacing();
							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Text("esp settings");
							ImGui::Spacing();
							ImGui::SliderInt("esp size", &Settings::Esp::esp_Size, 0, 10);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("size of each box");
							ImGui::SliderInt("bomb timer", &Settings::Esp::esp_BombTimer, 0, 65);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("useful for community servers(?) where bomb timer is different");

							ImGui::Spacing();
							ImGui::Separator();
							ImGui::Spacing();

							
						
							ImGui::PushItemWidth(150.f);
							ImGui::ColorEdit3("Chams CT", Settings::Esp::chams_Color_CT);
							ImGui::SameLine(SpaceLineTwo);
							ImGui::ColorEdit3("Chams Visible CT", Settings::Esp::chams_Color_VCT);

							ImGui::ColorEdit3("Chams T", Settings::Esp::chams_Color_TT);
							ImGui::SameLine(SpaceLineTwo);
							ImGui::ColorEdit3("Chams Visible T", Settings::Esp::chams_Color_VTT);
							ImGui::PopItemWidth();


						}
					}
					if (otherpages == 1)
					{

						
						const char* iHitSound[] =
						{
							"Off",
							"Default",
							"Anime",
							"Roblox",
							"GameSense",
							"German",
							"HeadMeme",
							"FadeCSGO.tk"
						};

				


						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Spacing();
						ImGui::Text("DISABLE HITMARKER/HITSOUND AND DAMAGEINDICATOR IF YOUR GAME CRASHS AFTER DEATH!");
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Spacing();

						ImGui::Text("Skybox Changer");
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("spoofs skybox to other map - buggy");
						ImGui::Spacing();
						if (ImGui::Combo("Skybox", &Settings::Misc::misc_CurrentSky, skybox_items, IM_ARRAYSIZE(skybox_items)))
						{
							Settings::Misc::misc_SkyName = skybox_items[Settings::Misc::misc_CurrentSky];
						}



						ImGui::Checkbox("No Sky", &Settings::Misc::misc_NoSky);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("SMAC BAN - Removes Sky");
						


						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("Wire Smoke", &Settings::Misc::misc_wireframesmoke);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("SMAC BAN, buggy while walking through smoke");
						ImGui::SameLine(SpaceLineOne);
						ImGui::Checkbox("No Smoke", &Settings::Misc::misc_NoSmoke);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("SMAC BAN, buggy while walking through smoke");
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("No Flash", &Settings::Misc::misc_NoFlash);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("disables rendering of flash blinding");



						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Text("Disable Damage Indicator if your Game crashs after you die");
						ImGui::Spacing();
						ImGui::Checkbox("Damage Indicator", &Settings::Esp::DamageIndicator);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Draws Damage Numbers next to enemy if hit - Disabled in Main Menu (crashfix)");
						{
							if (!Interfaces::Engine()->IsInGame())
								Settings::Esp::DamageIndicator = false;
						}

						ImGui::SameLine(SpaceLineTwo);
						ImGui::PushItemWidth(300.f);
						ImGui::ColorEdit3("Damager Color", Settings::Esp::DamagerColor);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Sets Color");
						ImGui::PopItemWidth();

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();


						ImGui::Text("Disable Hitmarker and Hitsounds if your Game crashs after you die");
						ImGui::Spacing();
						ImGui::Checkbox("Hit Marker", &Settings::Misc::misc_HitMarker);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Shows Crosshair when hit Enemy");
						ImGui::SameLine(SpaceLineTwo);
						ImGui::PushItemWidth(300.f);

						ImGui::ColorEdit3("Hit Color", Settings::Misc::misc_HitMarkerColor);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Hit Color");
						ImGui::PopItemWidth();
						ImGui::Combo("Hit Sound", &Settings::Misc::misc_HitMarkerSound, iHitSound, ARRAYSIZE(iHitSound));

						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Plays Sound on enemy hit");

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("Point Esp", &Settings::Radar::barrel);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Basically Out Of View ESP - Draws Points for Enemies");
					
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Text("Disable Hitmarker with Hitsounds or Damage Indicator if your Game crashs after you die");
						ImGui::Text("One of those Features causes crashes after death");

					}


					if (otherpages == 2)
					{
						g_pGui->bluefont();
						;
						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();
						ImGui::Checkbox("InGame", &Settings::Radar::rad_InGame);
						ImGui::PopItemWidth();
					}

					ImGui::EndChild();
					ImGui::EndGroup();
				}




				//----------------------------------------------------------------------------------------Changer-------------------------------------------------------------------------------------------------


			}
			else if (tabSelected == 2) // Skins
			{


				//[enc_string_disable /]

				g_pGui->bluefont();
				ImGui::BeginGroup();
			
				ImGui::BeginChild(1, ImVec2(-1, 680), true);
				{
					ImGui::Text("CHANGERS");
					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();
					ImGui::Text("Serverside Changers");
					ImGui::Spacing();
					ImGui::Checkbox("Profile Changer - only works with a Rank and from lvl 3", &Settings::Misc::window_profilechanger);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Serversided - in lobby");
				

					ImGui::Checkbox("Medal changer - only works from lvl 2", &Settings::Misc::window_medalchanger);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("Serversided - in lobby AND in game");
					

					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();

					ImGui::Text("Clientsided Changers");
					ImGui::Spacing();

					ImGui::Checkbox("Skinchanger", &Settings::Misc::misc_SkinChanger);			
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("clientsided - you're the only one who can see those Skins");

					ImGui::Checkbox("Inventory Changer - only works from lvl 3", &Settings::Misc::window_inventorychanger);
					if (ImGui::IsItemHovered())
						ImGui::SetTooltip("clientsided - you're the only one who can see it");
		


					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();

					ImGui::Text("Filters");
					ImGui::Spacing();
					ImGui::Checkbox("Skin Ids", &Settings::Misc::skinids);
					ImGui::SameLine(SpaceLineOne);
					ImGui::Checkbox("Weapon Ids", &Settings::Misc::weaponids);
					ImGui::SameLine(SpaceLineTwo);
					ImGui::Checkbox("Medal Ids", &Settings::Misc::medalids);
					ImGui::SameLine(SpaceLineThr);
					ImGui::Checkbox("Sticker Ids", &Settings::Misc::stickerids);
					ImGui::Spacing();
					ImGui::Separator();
					ImGui::Spacing();

					ImGui::EndChild();
					ImGui::EndGroup();
				}
				//------------------------------------------------------------------------------------------Misc---------------------------------------------------------------------------------------------------

			}
			else if (tabSelected == 3) // Misc
			{
				g_pGui->bluefont();
				ImGui::BeginGroup();
				ImGui::BeginChild(1, ImVec2(-1, 680), true);
				{

					ImGui::BeginGroup();

					ImGui::Text("MISC");
					ImGui::Separator();

					static int otherpages = 0;



					if (ImGui::Button("Misc 1", ImVec2(260.0f, 25.0f))) // <---- customize these to your liking.
					{
						otherpages = 0;
					}
					ImGui::SameLine();
					if (ImGui::Button("Misc 2", ImVec2(260.0f, 25.0f))) // <---- again, customize to your liking.
					{
						otherpages = 1;
					}
					ImGui::SameLine();
					if (ImGui::Button("Knifebot", ImVec2(260.0f, 25.0f))) // <---- again, customize to your liking.
					{
						otherpages = 2;
					}

					ImGui::Separator();

					if (otherpages == 0)
					{
						ImGui::BeginGroup();

						ImGui::Spacing();

						/*	ImGui::Checkbox("rainbow menu", &Settings::Misc::misc_RainbowMenu);
							if (ImGui::IsItemHovered())
								ImGui::SetTooltip("does not work anymore on main window");
							ImGui::PushItemWidth(362.f);
							if (ImGui::InputFloat("fade speed", &Settings::Misc::misc_RainbowSpeed, 0.001f, 0.01f))
							{
								if (Settings::Misc::misc_RainbowSpeed < 0.001f)
									Settings::Misc::misc_RainbowSpeed = 0.001f;
								if (Settings::Misc::misc_RainbowSpeed > 0.01f)
									Settings::Misc::misc_RainbowSpeed = 0.01f;
							};
							*/



						ImGui::Hotkey("Menu Key", &Settings::menu_key, ImVec2(100, 25));
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("Anti Afk", &Settings::Misc::misc_AntiAfk);


						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Checkbox("Bhop", &Settings::Misc::misc_Bhop);
						ImGui::SameLine(SpaceLineTwo);
						const char* strafe[] = { "none" , "legit" };
						ImGui::Combo("Auto Strafe", &Settings::Misc::misc_AutoStrafe, strafe, IM_ARRAYSIZE(strafe));

						ImGui::Checkbox("inventory always on", &Settings::Misc::invalwayson);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("allows you to access inventory in competitive match post-warmup");


						ImGui::Checkbox("Sniper Crosshair", &Settings::Misc::misc_AwpAim);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Draws a Dot if you use a Sniper");
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("Random Chat Spam", &Settings::Misc::misc_spamrandom);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("trashtalks chat creatively");



						ImGui::Checkbox("Chat Spam", &Settings::Misc::misc_spamregular);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Trashtalks Chat");
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("Spectators", &Settings::Misc::misc_Spectators);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Shows Spectators");




						ImGui::Checkbox("Auto Accept", &Settings::Misc::misc_AutoAccept);
						ImGui::SameLine(SpaceLineTwo);
						ImGui::Checkbox("Kill Spam", &Settings::Misc::Killmessage);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("trashtalks after Killing someone");

						ImGui::Checkbox("Radio Spam", &Settings::Misc::misc_radiospam);
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Spam Commands");



						ImGui::Spacing();


						ImGui::Separator();
						ImGui::Spacing();

						string clan_1 = "clear";
						string clan_2 = "Negerjaeger.cc";
						string clan_3 = "Negerjaeger.cc Animated";
						const char* items5[] = { clan_1.c_str() , clan_2.c_str() , clan_3.c_str()};
						ImGui::Combo("clantag changer", &Settings::Misc::misc_Clan, items5, IM_ARRAYSIZE(items5));
						if (ImGui::IsItemHovered())
							ImGui::SetTooltip("Clantag Changer");

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();


						ImGui::Checkbox("Fov Changer", &Settings::Misc::misc_FovChanger);
						ImGui::PushItemWidth(362.f);
						ImGui::SliderInt("Fov View", &Settings::Misc::misc_FovView, 1, 190);
						ImGui::SliderInt("Fov Model View", &Settings::Misc::misc_FovModelView, 1, 190);

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

						ImGui::Text("Negerjaeger.cc Coded by Tiokun,JazzFree");
						ImGui::Text("Negerjaeger.cc Sherlock Holmes sucked btw");
						ImGui::Text("Negerjaeger.cc > ALL");

						ImGui::EndGroup();
					}
					if (otherpages == 1)
					{

						ImGui::BeginGroup();

						ImGui::Spacing();


						static char buf2[128] = { 0 };
						ImGui::Text("Custom Name");
						ImGui::InputText("##CustomName", buf2, 16, Settings::Misc::misc_NameChange);
						if (ImGui::Button("apply custom name")) {
							ConVar* Name = Interfaces::GetConVar()->FindVar("name");
							*(int*)((DWORD)&Name->fnChangeCallback + 0xC) = 0;
							Name->SetValue(buf2);
						}

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();



						static char misc_CustomClanTag[128] = { 0 };
						ImGui::Text("Custom Clantag");
						ImGui::InputText("##CustomClanTag", misc_CustomClanTag, 128);

						if (ImGui::Button("apply custom clantag"))
						{
							Engine::ClanTagApply(misc_CustomClanTag);
						}

						ImGui::Spacing();
						ImGui::Separator();
						ImGui::Spacing();

					}

					if (otherpages == 2)
					{

						ImGui::BeginGroup();
						ImGui::Spacing();

						ImGui::Checkbox("Active", &Settings::Knifebot::knf_Active);
						ImGui::Checkbox("Attack Team", &Settings::Knifebot::knf_Team);

						ImGui::Separator();

						string attack_1 = "attack 1";
						string attack_2 = "attack 2";
						string attack_3 = "both";

						const char* items[] = { attack_1.c_str() , attack_2.c_str() , attack_3.c_str() };
						ImGui::Combo("Attack Type", &Settings::Knifebot::knf_Attack, items, IM_ARRAYSIZE(items));

						ImGui::Separator();

						ImGui::SliderInt("Distance to Attack 1", &Settings::Knifebot::knf_DistAttack, 1, 60);
						ImGui::SliderInt("Distance to Attack 2", &Settings::Knifebot::knf_DistAttack2, 1, 60);

						ImGui::EndGroup();

					}
					ImGui::EndChild();
					ImGui::EndGroup();
				}

			}
			ImGui::EndGroup();
			ImGui::End();

		}
	}
}






