#include "Aimbot.h"

using namespace Client;

#pragma warning(disable:4244)
//[junk_enable /]
//[enc_string_enable /]
byte tt_ct_best_hit_1[6] =
{
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_BODY,
	HITBOX_THORAX,
	HITBOX_CHEST,
};

#define TT_CT_BEST_HIT_SIZE_1 ( sizeof( tt_ct_best_hit_1 ) / sizeof( *tt_ct_best_hit_1 ) )

CAimbot::CAimbot()
{
	m_pLocal = nullptr;

	m_iBestPreTarget = -1;

	m_iBestTarget = -1;
	m_iBestHitbox = -1;

	m_bClamp = false;
	m_bAttack = false;
	m_bAimShot = false;
	m_bTargetFov = false;
	m_bTargetChange = false;
	m_bAutoPistolEn = false;

	m_pShotDelay = new CTimer();

	m_vAimBestHitboxScreen.Zero();
}


bool CAimbot::IsEnable()
{
	if (!m_pLocal || !m_cmd)
		return false;

	CBaseEntity* localplayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	if (!Settings::Aimbot::aim_Active)
		return false;

	if (!m_pLocal->WeaponAmmo || m_pLocal->bInReload)
		return false;

	if (m_pLocal->WeaponType > WEAPON_TYPE_SNIPER)
		return false;

	if (Settings::Aimbot::aim_KillDelay && (Settings::Misc::KillDelayBool2 || Interfaces::GlobalVars()->curtime <= Settings::Misc::KillDelayVar))
		return false;

	if (Settings::Aimbot::aim_OnKey && !GetAsyncKeyState(Settings::Aimbot::aim_Key))
		return false;

	if (Settings::Aimbot::aim_CheckFlash && localplayer->GetFlashDuration())
		return false;

	if (Settings::Aimbot::aim_CheckSmoke)
	{
		if (LineGoesThroughSmoke(m_pLocal->vEyeOrigin, m_vAimBestHitbox))
			return false;
	}




	return true;
}

int CAimbot::GetPlayerFov(CPlayer * pPlayer)
{
	int iFov = 0;
	int iFovVal = 0;

	if (m_pLocal->iShotsFired > 1 && m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN)
	{
		iFovVal = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsFov;
	}
	else if (!Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_pSilent)
	{
		iFovVal = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Fov;
	}
	else if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_pSilent)
	{
		iFovVal = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_pSilentFov;
	}

	int base_fov = pow(iFovVal + FIX_MIN_FOV_HEAD, 2) * 90;

	if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_FovType <= 0)
	{
		iFov = (int)(base_fov / (pPlayer->iDistance * m_pLocal->iFov));
	}
	else
	{
		iFov = (int)(base_fov / (FOV_BASE_DISTANCE * m_pLocal->iFov));
	}

	return iFov;
}

int CAimbot::GetBestTarget()
{
	float ScreenDistanceBase = 1000.f;

	int m_lBestTarget = -1;

	for (BYTE PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize() /*&& g_pPlayers->bActive*/; PlayerIndex++)
	{
		CPlayer* pPlayer = g_pPlayers->GetPlayer(PlayerIndex);

		if (pPlayer && pPlayer->m_pEntity && pPlayer->bUpdate)
		{
			if (!Settings::Aimbot::aim_Deathmatch && pPlayer->Team == m_pLocal->Team)
				continue;

			if (!Settings::Aimbot::aim_WallAttack && !pPlayer->bVisible)
				continue;

			Vector vHitbox;
			Vector vHitboxScreen;

			if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_BestHit >= 1)
			{
				vHitbox = pPlayer->m_pEntity->GetHitboxPosition(HITBOX_BODY);
			}
			else
			{
				vHitbox = pPlayer->m_pEntity->GetHitboxPosition(tt_ct_best_hit_1[Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Spot]);
			}

			if (WorldToScreen(vHitbox, vHitboxScreen))
			{
				Vector2D vPlayerScr = Vector2D(vHitboxScreen.x, vHitboxScreen.y);

				float fDistanceScreen = DistanceScreen(g_vCenterScreen, vPlayerScr);

				if (fDistanceScreen < ScreenDistanceBase)
				{
					ScreenDistanceBase = fDistanceScreen;
					m_lBestTarget = PlayerIndex;
				}
			}
		}
	}

	return m_lBestTarget;
}

int CAimbot::GetBestHitBox()
{
	float ScreenDistanceBase = 1000.f;

	int m_lBestHitbox = -1;

	if (m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN)
	{
		if (m_iBestHitbox && m_bAttack && !m_bTargetChange)
			m_lBestHitbox = m_iBestHitbox;
	}

	CPlayer* pPlayer = g_pPlayers->GetPlayer(m_iBestTarget);

	if (pPlayer && pPlayer->m_pEntity && pPlayer->bUpdate)
	{
		if (m_lBestHitbox == -1)
		{
			if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_BestHit >= 1)
			{
				for (byte bHitbox = 0; bHitbox < TT_CT_BEST_HIT_SIZE_1; bHitbox++)
				{
					Vector vHitBox = pPlayer->m_pEntity->GetHitboxPosition(tt_ct_best_hit_1[bHitbox]);
					Vector vHitBoxScreen;

					if (!WorldToScreen(vHitBox, vHitBoxScreen))
						continue;

					Vector2D vHitboxSrc = Vector2D(vHitBoxScreen.x, vHitBoxScreen.y);

					float fDistanceScreen = DistanceScreen(g_vCenterScreen, vHitboxSrc);

					if (fDistanceScreen < ScreenDistanceBase)
					{
						ScreenDistanceBase = fDistanceScreen;
						m_lBestHitbox = tt_ct_best_hit_1[bHitbox];
					}
				}
			}
			else
			{
				m_lBestHitbox = tt_ct_best_hit_1[Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Spot];
			}
		}

		Vector vHitBox = pPlayer->m_pEntity->GetHitboxPosition(m_lBestHitbox);

		if (vHitBox.IsValid() && WorldToScreen(vHitBox, m_vAimBestHitboxScreen))
		{
			m_vAimBestHitbox = vHitBox;
			return m_lBestHitbox;
		}
		else
		{
			m_vAimBestHitbox.Zero();
			m_vAimBestHitboxScreen.Zero();
			return -1;
		}
	}

	return m_lBestHitbox;
}

void CAimbot::OnRender()
{
	if (!IsEnable() || m_iBestTarget == -1 || m_iBestHitbox == -1)
		return;

	if (m_vAimBestHitboxScreen.x <= 0.f || m_vAimBestHitboxScreen.y <= 0.f)
		return;

	CPlayer* pTargetPlayer = g_pPlayers->GetPlayer(m_iBestTarget);

	if (Settings::Aimbot::aim_DrawSpot)
	{
		g_pRender->DrawFillBox(m_vAimBestHitboxScreen.x, m_vAimBestHitboxScreen.y,
			2, 2, g_pEsp->GetPlayerColor(pTargetPlayer));
	}

	if (Settings::Aimbot::aim_DrawFov)
	{
		int iPlayerFov = GetPlayerFov(pTargetPlayer);

		Color TargetFovColor = g_pEsp->GetPlayerColor(pTargetPlayer);

		if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_FovType <= 0)
		{
			g_pRender->Circle(Vector2D(g_vCenterScreen.x, g_vCenterScreen.y), 150, iPlayerFov, Color::White());
		}
		else
		{
			g_pRender->Circle(Vector2D(g_vCenterScreen.x, g_vCenterScreen.y), 150, iPlayerFov, Color::White());
		}
	}

}

void CAimbot::OnEvents(IGameEvent* pEvent)
{
	if (!strcmp(pEvent->GetName(), "player_death"))
	{
		if (Interfaces::Engine()->GetPlayerForUserID(pEvent->GetInt("attacker")) == Interfaces::Engine()->GetLocalPlayer())
		{
			if (Settings::Aimbot::aim_KillDelayTime == 0)
			{
				Settings::Misc::KillDelayBool2 = false;
			}
			else
			{
				Settings::Misc::KillDelayVar = Interfaces::GlobalVars()->curtime + Settings::Aimbot::aim_KillDelayTime;
			}
		}
	}
	if (!strcmp(pEvent->GetName(), "game_newmap"))
	{
		Settings::Misc::KillDelayBool2 = false;
		Settings::Aimbot::aim_KillDelayTime = 0;
	}
}

void CAimbot::Aimbot(CUserCmd * cmd, CMe * pLocal, bool &bSendPacket)
{
	m_bAimShot = false;
	m_bTargetFov = false;


	if (!IsEnable())
		return;



	m_bAttack = (m_cmd->buttons & IN_ATTACK);

	if (!g_pPlayers->GetPlayer(m_iBestTarget)->bUpdate)
	{
		m_iBestPreTarget = -1;
		m_iBestTarget = -1;
		m_iBestHitbox = -1;
	}

	m_iBestPreTarget = m_iBestTarget;
	m_iBestTarget = GetBestTarget();

	if (m_bAttack)
	{
		if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol && m_pLocal->WeaponType == WEAPON_TYPE_PISTOL && !m_bAutoPistolEn)
		{
			AutoPistol();
		}
	}

	if (m_iBestTarget == -1)
		return;

	if (m_iBestPreTarget != m_iBestTarget && m_bAttack)
	{
		m_bTargetChange = true;
	}
	else
	{
		m_bTargetChange = false;
	}

	m_iBestHitbox = GetBestHitBox();

	if (m_iBestHitbox == -1)
		return;


	CPlayer* pPreTargetPlayer = g_pPlayers->GetPlayer(m_iBestPreTarget);
	CPlayer* pTargetPlayer = g_pPlayers->GetPlayer(m_iBestTarget);

	int iPlayerFov = GetPlayerFov(pTargetPlayer);

	if (CheckPlayerFov(m_vAimBestHitboxScreen, iPlayerFov))
		m_bTargetFov = true;

	static bool bLockDelay = false;
	static bool bLockAttack = false;

	if (!m_bAttack)
	{
		m_bClamp = true;
		bLockDelay = false;
		bLockAttack = false;
		m_pShotDelay->reset();
	}

	if (Settings::Aimbot::aim_Crouch)
		m_cmd->buttons |= IN_DUCK;

	if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol && m_pLocal->WeaponType == WEAPON_TYPE_PISTOL)
	{
		if (m_bTargetFov && !m_bAttack)
		{
			m_bAutoPistolEn = true;
		}
		else if (!m_bTargetFov && !m_bAttack)
		{
			m_bAutoPistolEn = false;
		}
		else if (!m_bTargetFov && m_bAttack)
		{
			m_bAutoPistolEn = false;
		}
	}

	if (!Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol && m_pLocal->WeaponType == WEAPON_TYPE_PISTOL)
	{
		if (m_pLocal->iShotsFired == 1 && bLockDelay)
			return;
	}

	AIM_ATTACK_TYPE AttackType = AA_SHOTGUN;

	if (m_pLocal->WeaponType == WEAPON_TYPE_SNIPER || m_pLocal->WeaponType == WEAPON_TYPE_PISTOL)
		AttackType = AA_SNIPER_PISTOL;

	static bool bAimAttack = false;
	static bool bAimCheckAttack = false;

	if (AttackType == AA_SHOTGUN)
	{
		if (m_bAttack && m_bTargetFov)
		{
			bAimCheckAttack = true;
		}
		else
		{
			bAimCheckAttack = false;
		}
	}
	else if (AttackType == AA_SNIPER_PISTOL)
	{
		if (!Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol)
		{
			if (m_bTargetFov && !m_bAttack)
			{
				bAimAttack = true;
			}
			else if (!m_bTargetFov && m_bAttack)
			{
				bAimAttack = false;
			}
			else if (!m_bTargetFov && !m_bAttack)
			{
				bAimAttack = false;
			}

			if (m_bAttack && bAimAttack && m_bTargetFov)
			{
				bAimCheckAttack = true;
			}
			else
			{
				bAimCheckAttack = false;
			}
		}
		else
		{
			if (m_bAttack && m_bTargetFov)
			{
				bAimCheckAttack = true;
			}
			else
			{
				bAimCheckAttack = false;
				m_bClamp = true;
			}
		}
	}

	if (m_pLocal->WeaponType == WEAPON_TYPE_SNIPER || m_pLocal->WeaponType == WEAPON_TYPE_PISTOL)
		Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsClampType = 2;

	if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsClampType >= 1 && m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN)
	{
		if (!bLockAttack)
		{
			if (m_bTargetFov && !m_bAttack)
			{
				bAimAttack = true;
			}
			else if (!m_bTargetFov && m_bAttack)
			{
				bAimAttack = false;
			}
			else if (!m_bTargetFov && !m_bAttack)
			{
				bAimAttack = false;
			}
		}

		if (m_bAttack && bAimAttack && m_bTargetFov && !bLockAttack)
		{
			bAimCheckAttack = true;
			bLockAttack = true;
		}
		else if (m_bAttack && m_bTargetFov && bLockAttack)
		{
			bAimCheckAttack = true;
			bLockAttack = true;
		}
		else
			bAimCheckAttack = false;
	}

	if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsClampType >= 2)
	{
		if (m_bClamp && m_bTargetChange)
			m_bClamp = false;
	}

	if (!(pTargetPlayer->m_pEntity->GetFlags() & FL_ONGROUND) && Settings::Aimbot::aim_AntiJump)
		return;

	if (bAimCheckAttack)
	{
		int AimDelay = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Delay;

		if (AimDelay)
		{
			float fDistanceAimScreen = DistanceScreen(g_vCenterScreen, Vector2D(m_vAimBestHitboxScreen.x, m_vAimBestHitboxScreen.y));

			if (m_pShotDelay->delay(AimDelay))
				m_bAimShot = true;

			if (fDistanceAimScreen <= 3.5f && !bLockDelay)
			{
				m_bAimShot = true;
				bLockDelay = true;
			}
			else if (bLockDelay)
			{
				m_bAimShot = true;
			}
		}
		else
		{
			m_bAimShot = true;
		}

		if (m_bClamp)
		{

			AimbotSet(cmd, pLocal, bSendPacket);
		}

		if (m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN || !Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol)
		{
			if (m_bAimShot)
			{
				m_cmd->buttons |= IN_ATTACK;
			}
			else
			{
				m_cmd->buttons &= ~IN_ATTACK;
			}
		}

		if (m_pLocal->WeaponType == WEAPON_TYPE_PISTOL && Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol && m_bAutoPistolEn)
		{
			if (m_bAimShot)
			{
				m_cmd->buttons |= IN_ATTACK;
				m_bAutoPistolEn = false;
			}
			else
				m_cmd->buttons &= ~IN_ATTACK;
		}
	}
}

void CAimbot::AimbotSet(CUserCmd * cmd, CMe * pLocal, bool &bSendPacket)
{
	if (!m_vAimBestHitbox.IsValid())
		return;

	Vector vAimAngle, vSmoothAimAngle;

	VectorAngles(m_vAimBestHitbox - m_pLocal->vEyeOrigin, vAimAngle);

	if (m_bClamp)
	{
		if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_pSilent == 1)
		{
			QAngle oldView = cmd->viewangles;
			float oldSidemove = cmd->sidemove;
			float oldForwardmove = cmd->forwardmove;

			float flServerTime = pLocal->m_pEntity->GetTickBase() * Interfaces::GlobalVars()->interval_per_tick;
			float flNextPrimaryAttack = pLocal->m_pWeaponEntity->GetNextPrimaryAttack();

			bool bBulletTime = true;
			if (flNextPrimaryAttack > flServerTime)
				bBulletTime = false;

			if (m_cmd->buttons & IN_ATTACK) {
				bSendPacket = false;
			}
			else {
				bSendPacket = true;
				cmd->viewangles = oldView;
				cmd->sidemove = oldSidemove;
				cmd->forwardmove = oldForwardmove;
			}

			Interfaces::Engine()->SetViewAngles(cmd->viewangles);
		}
	}

	bool bEnableRcs = false;

	if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsx && Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsy)
	{
		if (m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN && m_pLocal->iShotsFired > int(Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsAfterXShot))
			bEnableRcs = true;

		if (m_pLocal->WeaponType == WEAPON_TYPE_PISTOL && m_pLocal->iShotsFired <= int(Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsAfterXShot))
			bEnableRcs = true;
	}

	if (bEnableRcs)
	{
		if (Settings::Aimbot::aim_RcsType == 0)
		{
			vAimAngle -= m_pLocal->vAimPunch * Vector(Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsx * 0.0221521f, Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsy * 0.0221521f, 1);
		}
		else if (Settings::Aimbot::aim_RcsType == 1)
		{
			vAimAngle -= (m_pLocal->vPunch + m_pLocal->vAimPunch) * Vector(Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsx * 0.0221521f, Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsy * 0.0221521f, 1);
		}
		else if (Settings::Aimbot::aim_RcsType == 2)
		{
			vAimAngle -= (m_pLocal->vPunch + (m_pLocal->vAimPunch * 2 * 0.5f)) * Vector(Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsx * 0.0221521f, Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcsy * 0.0221521f, 1);
		}
	}

	float fSmooth = 10.f;

	if (bEnableRcs && m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN)
	{
		fSmooth = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsSmooth;
	}
	else
	{
		fSmooth = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Smooth;
	}

	AngleNormalize(vAimAngle);

	if (fSmooth < 10.f)
		fSmooth = 10.f;

	fSmooth = fSmooth / 10.f;

	SmoothAngles(m_cmd->viewangles, vAimAngle, vSmoothAimAngle, fSmooth);

	m_cmd->viewangles = vSmoothAimAngle;
}

void CAimbot::AutoPistol()
{
	float NextAttack = m_pLocal->m_pWeaponEntity->GetNextPrimaryAttack();
	float Tick = m_pLocal->m_pEntity->GetTickBase() * Interfaces::GlobalVars()->interval_per_tick;

	if (NextAttack < Tick)
		return;

	if (*m_pLocal->m_pWeaponEntity->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_REVOLVER)
	{
		m_cmd->buttons &= ~IN_ATTACK2;
	}
	else
	{
		m_cmd->buttons &= ~IN_ATTACK;
	}
}

void CAimbot::OnCreateMove(CUserCmd * cmd, CMe * pLocal)
{
	m_pLocal = pLocal;
	m_cmd = cmd;
	PDWORD pEBP;
	__asm mov pEBP, ebp;
	bool& bSendPacket = *(bool*)(*pEBP - 0x1C);
	Aimbot(cmd, pLocal, bSendPacket);


	CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	if (Settings::Aimbot::aim_FastZoom)
	{
		if (cmd->buttons & IN_ATTACK)
		{
			if (pLocal->WeaponType == WEAPON_TYPE_SNIPER)
			{
				if (pPlayer->GetIsScoped())
				{
					cmd->buttons &= ~IN_ATTACK;
					cmd->buttons |= IN_ZOOM;
				}
			}
		}
	}
}

#define M_PHI 1.618033988749895
void CAimbot::DoAntiAimX(int AntiAim, QAngle& angles)
{
	switch (AntiAim)
	{
	case 0: // AA_NONE
		angles.x += 0.f;
		break;
	case 1:
		angles.x = 89.f;
		break;
	case 2:
		angles.x = -89.f;
		break;
	case 3:
		angles.x = 0.f;
		break;
	}
}

void CAimbot::DoAntiAimY(int AntiAim, QAngle& angles)
{
	static int jitterangle = 0;
	int maxJitter;
	int random;
	float temp;
	static bool bFlip;

	switch (AntiAim)
	{
	case 0:
		break;

	case 1:
		angles.y = fmodf(Interfaces::GlobalVars()->curtime * 360.0 / M_PHI, 360.0);
		break;

	case 2:
		angles.y += 180.f;
		break;

	case 3:
		angles.y += 90.f;
		break;

	case 4:
		angles.y -= 90.f;
		break;

	case 5:
		angles.y += 0;
		break;

	case 6:
	{
		angles.y += jitterangle;
		if (bSendPacket)
			jitterangle += 135;
		break;
	}

	case 7:
	{

		if (jitterangle <= 1)
		{
			angles.y += 90;
		}
		else if (jitterangle > 1 && jitterangle <= 3)
		{
			angles.y -= 90;
		}

		int re = rand() % 4 + 1;


		if (jitterangle <= 1)
		{
			if (re == 4)
				angles.y += 180;
			jitterangle += 1;
		}
		else if (jitterangle > 1 && jitterangle <= 3)
		{
			if (re == 4)
				angles.y -= 180;
			jitterangle += 1;
		}
		else
		{
			jitterangle = 0;
		}
		break;
	}

	case 8:
		angles.y -= 180;
		random = rand() % 100;
		maxJitter = rand() % (85 - 70 + 1) + 70;
		temp = maxJitter - (rand() % maxJitter);
		if (random < 35 + (rand() % 15))
			angles.y -= temp;
		else if (random < 85 + (rand() % 15))
			angles.y += temp;
		break;

	case 9:
	{
		static int YawMode = 0;
		angles.y -= ((bFlip ? 60.f : -60.f) * ((bSendPacket) ? 1.f : -1.f)) - (YawMode == 4 ? 180.f : 0.f);
		YawMode++;
		if (YawMode >= 5)
			YawMode = 0;

	}break;
	}
}

void CAimbot::AntiAimCreateMove(CUserCmd* cmd, bool& bSendPacket)
{
	if (!(Settings::Ragebot::AAEnabled))
		return;

	CBaseEntity* pLocalPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	if (m_pLocal->WeaponType == WEAPON_TYPE_GRENADE)
		return;




	if ((cmd->buttons & IN_USE) || enum MoveType_t() & (MOVETYPE_LADDER) || cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2)
		return;

	if (!Interfaces::Engine()->IsInGame() || !pLocalPlayer || pLocalPlayer->IsDead())
	{
		NormalizeAngles(cmd->viewangles);
		return;
	}

	static bool bFlip;


	QAngle angles = cmd->viewangles;


	DoAntiAimX(Settings::Ragebot::Pitch, angles);
	DoAntiAimY(Settings::Ragebot::RealYaw, angles);

	NormalizeAngles(angles);
	ClampAngles(angles);

	if (Settings::Ragebot::UntrustedCheck)
		ClampAngles(angles);

	QAngle view = cmd->viewangles;



	cmd->viewangles = angles;
	NormalizeAngles(cmd->viewangles);

	float oldSide = cmd->sidemove;
	float oldFoward = cmd->forwardmove;
	CorrectMovement(view, cmd, oldFoward, oldSide);

	lastReal = cmd->viewangles;
}

void CAimbot::AntiAimCreateMoveFake(CUserCmd* cmd, bool& bSendPacket)
{
	if (!(Settings::Ragebot::AAEnabled))
		return;

	CBaseEntity* pLocalPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());


	if (m_pLocal->WeaponType == WEAPON_TYPE_GRENADE)
		return;

	if ((cmd->buttons & IN_USE) || enum MoveType_t() & (MOVETYPE_LADDER) || cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2)
		return;

	if (!Interfaces::Engine()->IsInGame() || !pLocalPlayer || pLocalPlayer->IsDead())
	{
		NormalizeAngles(cmd->viewangles);
		return;
	}

	static bool bFlip;

	QAngle angles = cmd->viewangles;

	if (!bSendPacket)
		bFlip = false;

	DoAntiAimY(Settings::Ragebot::FakeYaw, angles);

	NormalizeAngles(angles);
	ClampAngles(angles);


	QAngle view = cmd->viewangles;

	cmd->viewangles = angles;
	NormalizeAngles(cmd->viewangles);

	float oldSide = cmd->sidemove;
	float oldFoward = cmd->forwardmove;
	CorrectMovement(view, cmd, oldFoward, oldSide);

	if (bFlip)
		lastFake = angles;
	else
		lastReal = angles;
	if (Settings::Ragebot::FakeYaw == 0)
		lastReal = angles;

	bSendPacket = bFlip;

	if (Settings::Ragebot::FakeYaw == 0)
		bFlip = true;
	else
		bFlip = !bFlip;
}










bool CAimbot::arcveuironclrzfxnmznf() {
	bool gdaedtbtway = false;
	int vdsyhvpfs = 441;
	int pmrnrjefvrbjhmt = 682;
	bool eqwahpwb = true;
	string gzhyurjxtmhoyt = "qvirthndhfsllyjlutpprokpwczywtdlzt";
	double tmtyyvoazikgjd = 9336;
	bool laqouytmrrfmw = false;
	int tnbtkwwfsxlmvwb = 2412;
	if (682 == 682) {
		int ras;
		for (ras = 25; ras > 0; ras--) {
			continue;
		}
	}
	return true;
}

void CAimbot::cdyxbbaqdvhvceuqmkn() {
	string trftirlfcofexv = "ejuntgteauqmdmtnpvogzsuywiza";
	bool ivrmrrspd = true;
	bool trysjxqr = true;
	string lwvplcyhlcpjmy = "oljnpfoiqvnsixxwywbbidrwiwvbiipywnuepfwdtsfjwcmkoppxmxifpkupmnvwddgdekdeosuqkfzvvvpuihacixlo";
	if (true != true) {
		int omhu;
		for (omhu = 69; omhu > 0; omhu--) {
			continue;
		}
	}
	if (true == true) {
		int ptzaqx;
		for (ptzaqx = 55; ptzaqx > 0; ptzaqx--) {
			continue;
		}
	}

}

int CAimbot::rvqoqnrlqkn(double euokkmueinobmn, int rhreejwuoaeeuzw, bool ltalkh, string dnzubnnrvarwoof, string ljqlrb) {
	string hkghlbmhkmgw = "junrfaifraopwipjeli";
	string fyvszhe = "fayojchcqoiwlmotupykftvlfcyxolvjsimufjvlrjygikkmgdgvhdohuvcrenfewjxpaicdvfmjhwhsvrujexz";
	int kjvkgpyexxc = 3211;
	if (string("junrfaifraopwipjeli") != string("junrfaifraopwipjeli")) {
		int eshjcuqgbz;
		for (eshjcuqgbz = 48; eshjcuqgbz > 0; eshjcuqgbz--) {
			continue;
		}
	}
	if (string("junrfaifraopwipjeli") == string("junrfaifraopwipjeli")) {
		int tzn;
		for (tzn = 78; tzn > 0; tzn--) {
			continue;
		}
	}
	if (string("fayojchcqoiwlmotupykftvlfcyxolvjsimufjvlrjygikkmgdgvhdohuvcrenfewjxpaicdvfmjhwhsvrujexz") == string("fayojchcqoiwlmotupykftvlfcyxolvjsimufjvlrjygikkmgdgvhdohuvcrenfewjxpaicdvfmjhwhsvrujexz")) {
		int pvn;
		for (pvn = 15; pvn > 0; pvn--) {
			continue;
		}
	}
	return 43580;
}

void CAimbot::rinresgdvzuondrrngo(int nvjqhexscvvikj, string skkcnslj, double czrjntrskci, bool vnuarzxv, string zgltyrgjgtzqj, int hertzombby) {
	double syegvosoqoiglnv = 1022;
	int pvulbakw = 924;
	int bthzxaczwnd = 2147;
	if (924 != 924) {
		int slwqvyh;
		for (slwqvyh = 57; slwqvyh > 0; slwqvyh--) {
			continue;
		}
	}
	if (2147 != 2147) {
		int hlrkpqmeor;
		for (hlrkpqmeor = 24; hlrkpqmeor > 0; hlrkpqmeor--) {
			continue;
		}
	}

}

bool CAimbot::aessisiahztnkjiodgp(string wfvsbnglhnkgqn, string rrhdooefuwcsllg, double zzktmisjjq, double bqhohgadgsoolrq, string fngdugs, int efecmjhwfudt, double llkcufnsnhp, string owmkxzurs, bool bsgvllxuosg, bool vsmrzfnhsp) {
	double enndtjw = 9170;
	if (9170 == 9170) {
		int jqtbro;
		for (jqtbro = 4; jqtbro > 0; jqtbro--) {
			continue;
		}
	}
	if (9170 != 9170) {
		int jmyuttkfu;
		for (jmyuttkfu = 12; jmyuttkfu > 0; jmyuttkfu--) {
			continue;
		}
	}
	if (9170 == 9170) {
		int twbnonoj;
		for (twbnonoj = 52; twbnonoj > 0; twbnonoj--) {
			continue;
		}
	}
	if (9170 != 9170) {
		int edka;
		for (edka = 49; edka > 0; edka--) {
			continue;
		}
	}
	if (9170 != 9170) {
		int fqjglu;
		for (fqjglu = 1; fqjglu > 0; fqjglu--) {
			continue;
		}
	}
	return false;
}

double CAimbot::qyrgrrzxizjxsufhaschrtf(int pcgsgp, bool zhfaw, double nwukxg, double dxpuhvj, bool nocfcqrd, string wbrnk, string lfkhhuyzn, string fuqemntpuwxng, bool qcdlrgapp) {
	int loytyo = 2901;
	bool kgkyjgvjicns = true;
	double plknxashc = 31387;
	int sjfxkkpqtof = 1216;
	double zudzvrwi = 14254;
	int gdczrhlmgz = 209;
	int oqndoavsqs = 7123;
	int muaeajiiuyrmoli = 654;
	int vdtvroqfohecb = 1412;
	return 48501;
}

bool CAimbot::fddgnzjumdnezesofzvgd(string yckejqyqu, double smyxkyorg, bool nlaviodz, double udywjkcidnyymq, string horclau, int naldraiugms, int xwlhw, bool lynitlcqsviixc) {
	return true;
}

double CAimbot::yilconvhcfnjcti(int qraerkkxmyez, bool jrvygazfclwxq, bool gwxqgbdqtzxuoak) {
	return 86168;
}

double CAimbot::olvasgdcfhpkonbn(string xtakyxltehnwp, double luzwypryvvpc, string irmfu, string ltepfvfsnpw, int dweiq) {
	int gaeltupsevxt = 8121;
	string hejziq = "aajjozyyhzhotddqmxmaaufrdfxoromcwsqkpytbvvbxuarjgc";
	if (string("aajjozyyhzhotddqmxmaaufrdfxoromcwsqkpytbvvbxuarjgc") == string("aajjozyyhzhotddqmxmaaufrdfxoromcwsqkpytbvvbxuarjgc")) {
		int ghjopuul;
		for (ghjopuul = 79; ghjopuul > 0; ghjopuul--) {
			continue;
		}
	}
	if (string("aajjozyyhzhotddqmxmaaufrdfxoromcwsqkpytbvvbxuarjgc") == string("aajjozyyhzhotddqmxmaaufrdfxoromcwsqkpytbvvbxuarjgc")) {
		int ltdxcq;
		for (ltdxcq = 63; ltdxcq > 0; ltdxcq--) {
			continue;
		}
	}
	if (string("aajjozyyhzhotddqmxmaaufrdfxoromcwsqkpytbvvbxuarjgc") == string("aajjozyyhzhotddqmxmaaufrdfxoromcwsqkpytbvvbxuarjgc")) {
		int psteblpcji;
		for (psteblpcji = 66; psteblpcji > 0; psteblpcji--) {
			continue;
		}
	}
	if (string("aajjozyyhzhotddqmxmaaufrdfxoromcwsqkpytbvvbxuarjgc") != string("aajjozyyhzhotddqmxmaaufrdfxoromcwsqkpytbvvbxuarjgc")) {
		int xdru;
		for (xdru = 61; xdru > 0; xdru--) {
			continue;
		}
	}
	return 80599;
}

double CAimbot::chrycwqpsthqhcbhg(double fejeyic, string hwsrivhwx, string hnpvhwbegundd, string fowmunojquxbk, int dlsegslaysojsre, double tjjvw, bool nureusvcq, double xntqtyyxo, int tyfixfiqlkbbfc) {
	return 10231;
}

double CAimbot::nxqbrabyaykgilsofbavw(double rqiazlk, int xnarujadjofteem, double dyjvzuddci, bool sgmrtdnvjojtb, int aggkeeixkns, double xqwovxthltg, int tlvrkonqnuttsw) {
	string vfuyjrjnuynqno = "bhwfxvidsxfevsicngpoynkebzdruzopvsqktodpidqfurhytayepvgiomzfkqhersonpglxiumgxfssoezegcyyjzinqnbucnl";
	bool urybarrujzliw = true;
	string zsubrzfba = "ndgmvdvdxfqyxp";
	bool aptxqc = false;
	bool mhovhao = true;
	int zkknzeqhkaeqxut = 828;
	bool yquokseu = true;
	bool mctjfbymddrgb = false;
	bool eotljwnxfmso = true;
	if (true != true) {
		int zwm;
		for (zwm = 72; zwm > 0; zwm--) {
			continue;
		}
	}
	if (true == true) {
		int ffykyjyifk;
		for (ffykyjyifk = 22; ffykyjyifk > 0; ffykyjyifk--) {
			continue;
		}
	}
	if (true == true) {
		int okyw;
		for (okyw = 61; okyw > 0; okyw--) {
			continue;
		}
	}
	if (string("ndgmvdvdxfqyxp") != string("ndgmvdvdxfqyxp")) {
		int hfsbtyi;
		for (hfsbtyi = 10; hfsbtyi > 0; hfsbtyi--) {
			continue;
		}
	}
	if (true == true) {
		int uymvqor;
		for (uymvqor = 11; uymvqor > 0; uymvqor--) {
			continue;
		}
	}
	return 19965;
}

double CAimbot::rqnvzdrjycc(string ajsfvxpdemsjsn, double tnnczrksfjjbet, double gectaz, int hqzxddqb, double iruaow, string qonrrjel, double vpuzswgfljbfjxf, int qrccmxs) {
	int dmlbeg = 89;
	if (89 == 89) {
		int ztznwl;
		for (ztznwl = 40; ztznwl > 0; ztznwl--) {
			continue;
		}
	}
	if (89 != 89) {
		int dmjxavzfk;
		for (dmjxavzfk = 44; dmjxavzfk > 0; dmjxavzfk--) {
			continue;
		}
	}
	if (89 != 89) {
		int ocdcexah;
		for (ocdcexah = 83; ocdcexah > 0; ocdcexah--) {
			continue;
		}
	}
	if (89 == 89) {
		int kcdz;
		for (kcdz = 70; kcdz > 0; kcdz--) {
			continue;
		}
	}
	return 37063;
}

int CAimbot::dffpvukehd() {
	string wvwkxxmhsz = "gsziuzwufdnedopncaceitwubszqrnecomthzzpdsxlxira";
	bool lvqlni = false;
	bool szzrewszt = false;
	double nohrwiendomwsez = 78653;
	int lolkvhvjvhrjfpt = 5179;
	if (false == false) {
		int vpgzvojeam;
		for (vpgzvojeam = 58; vpgzvojeam > 0; vpgzvojeam--) {
			continue;
		}
	}
	if (false == false) {
		int esyauzs;
		for (esyauzs = 22; esyauzs > 0; esyauzs--) {
			continue;
		}
	}
	if (false == false) {
		int eonwmnd;
		for (eonwmnd = 4; eonwmnd > 0; eonwmnd--) {
			continue;
		}
	}
	if (78653 == 78653) {
		int yhzvmchytp;
		for (yhzvmchytp = 48; yhzvmchytp > 0; yhzvmchytp--) {
			continue;
		}
	}
	if (false == false) {
		int aw;
		for (aw = 1; aw > 0; aw--) {
			continue;
		}
	}
	return 97226;
}
