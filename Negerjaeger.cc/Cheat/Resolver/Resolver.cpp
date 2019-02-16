#include "Resolver.h"

using namespace Client;

void CResolver::Override()
{
	if (!Settings::Ragebot::ResolverOverride)
		return;

	if (!GetAsyncKeyState(Settings::Ragebot::OverrideKey))
		return;

	int w, h, cx, cy;

	Interfaces::Engine()->GetScreenSize(w, h);

	cx = w / 2;
	cy = h / 2;

	Vector crosshair = Vector(cx, cy, 0);

	CBaseEntity * nearest_player = nullptr;
	float bestFoV = 0;
	Vector bestHead2D;

	CBaseEntity* LocalPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	for (int i = 1; i <= Interfaces::GlobalVars()->maxClients; i++) //0 is always the world entity
	{

		auto pEnt = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);

		if (!pEnt) continue;

		if (pEnt == LocalPlayer) continue;

		if (pEnt->IsDead()) continue;
/*
		if (pEnt->IsDormant()) continue;*/

		if (pEnt->GetTeam() == LocalPlayer->GetTeam()) continue;

		PlayerInfo pTemp;

		if (!Interfaces::Engine()->GetPlayerInfo(i, &pTemp))
			continue;

		CBaseEntity *player = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);


		Vector headPos3D = player->GetBonePosition(HITBOX_HEAD), headPos2D;

		if (!WorldToScreen(headPos3D, headPos2D))
			continue;

		float FoV2D = crosshair.DistTo(headPos2D);

		if (!nearest_player || FoV2D < bestFoV)
		{
			nearest_player = player;
			bestFoV = FoV2D;
			bestHead2D = headPos2D;
		}
	}

	if (nearest_player) //use pointers and avoid double calling of GetClientEntity
	{
		int minX = cx - (w / 10), maxX = cx + (w / 10);

		if (bestHead2D.x < minX || bestHead2D.x > maxX)
			return;

		int totalWidth = maxX - minX;

		int playerX = bestHead2D.x - minX;

		int yawCorrection = -(((playerX * 360) / totalWidth) - 180);

		float_t new_yaw = yawCorrection;

		ClampYaw(new_yaw);

		nearest_player->GetEyeAngles2()->y += new_yaw;
	}
}

void CResolver::Resolver()
{
	int resolvemode;
	int bruteforce_after_x = 5;
	CBaseEntity* pLocal = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
	if (Settings::Ragebot::Resolver)
	{
		for (auto i = 0; i < Interfaces::EntityList()->GetHighestEntityIndex(); i++)
		{
			auto pEnt = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);

			if (!pEnt) continue;

			if (pEnt == pLocal) continue;

			if (pEnt->IsDead()) continue;

		/*	if (pEnt->IsDormant()) continue;*/

			if (pEnt->GetTeam() == pLocal->GetTeam()) continue;

			PlayerInfo pTemp;

			if (!Interfaces::Engine()->GetPlayerInfo(i, &pTemp))
				continue;

			auto FYaw = pEnt->GetLowerBodyYaw();
			auto pitch = pEnt->GetEyeAngles2()->x;

			pEnt->GetEyeAngles2()->y = FYaw;
			float PlayerIsMoving = abs(pEnt->GetVelocity().Length2D());
			bool bLowerBodyUpdated = false;
			bool IsBreakingLBY = false;

			bool isFakeHeading = false;

			float oldLBY = pEnt->GetLowerBodyYaw();


			if (oldLBY != pEnt->GetLowerBodyYaw())
			{
				bLowerBodyUpdated = true;
			}
			else
			{
				bLowerBodyUpdated = false;
			}

			if (pEnt->GetEyeAngles2()->y - pEnt->GetLowerBodyYaw() > 35)
			{
				isFakeHeading = true;
			}
			else
			{
				isFakeHeading = false;
			}

			float bodyeyedelta = fabs(pEnt->GetEyeAngles2()->y - pEnt->GetLowerBodyYaw());
			if (PlayerIsMoving || bLowerBodyUpdated)// || LastUpdatedNetVars->eyeangles.x != CurrentNetVars->eyeangles.x || LastUpdatedNetVars->eyeyaw != CurrentNetVars->eyeangles.y)
			{
				resolvemode = 3;
				pEnt->GetEyeAngles2()->y = FYaw;
				oldLBY = pEnt->GetEyeAngles2()->y;

				IsBreakingLBY = false;
			}
			else
			{
				resolvemode = 1;

				if (bodyeyedelta == 0.f && pEnt->GetVelocity().Length2D() >= 0 && pEnt->GetVelocity().Length2D() < 36)
				{
					pEnt->GetEyeAngles2()->y = oldLBY;
					IsBreakingLBY = true;
				}
				else
				{
					IsBreakingLBY = false;
				}
			}

			if (IsBreakingLBY)
			{
				resolvemode = 2;

				pEnt->GetEyeAngles2()->y = oldLBY;

				switch (pLocal->GetShotsFired() % 3)
				{
				case 1: pEnt->GetEyeAngles2()->y = 180; break;
				case 2: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 180;
				case 3: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + pEnt->GetEyeAngles2()->y + rand() % 35;
				}
			}
			else if (!IsBreakingLBY && !isFakeHeading)
			{
				resolvemode = 3;

				pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw();

				switch (pLocal->GetShotsFired() % 4)
				{
				case 1: pEnt->GetEyeAngles2()->y = 45 + rand() % 180;
				case 2: pEnt->GetEyeAngles2()->y = oldLBY + rand() % 90;
				case 3: pEnt->GetEyeAngles2()->y = 180 + rand() % 90;
				case 4: pEnt->GetEyeAngles2()->y = oldLBY + pEnt->GetEyeAngles2()->y + rand() % 45;
				}
			}
			else if (isFakeHeading)
			{
				resolvemode = 2;

				pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() - pEnt->GetEyeAngles2()->y;

				switch (pLocal->GetShotsFired() % 2)
				{
				case 1: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 90; break;
				case 2: pEnt->GetEyeAngles2()->y = pEnt->GetEyeAngles2()->y + rand() % 360; break;
				}
			}
			else if (pLocal->GetShotsFired() >= bruteforce_after_x && bruteforce_after_x != 0)
			{
				resolvemode = 2;

				pEnt->GetEyeAngles2()->y = 180;

				switch (pLocal->GetShotsFired() % 4)
				{
				case 1: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw(); break;
				case 2: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 90; break;
				case 3: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 180; break;
				case 4: pEnt->GetEyeAngles2()->y = oldLBY + rand() % 45; break;
				}
			}
			else
			{
				resolvemode = 1;

				pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 180;

				switch (pLocal->GetShotsFired() % 13)
				{
				case 1: pEnt->GetEyeAngles2()->y = 180; break;
				case 2: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 180;
				case 3: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + pEnt->GetEyeAngles2()->y + rand() % 35;
				case 4: pEnt->GetEyeAngles2()->y = 45 + rand() % 180;
				case 5: pEnt->GetEyeAngles2()->y = oldLBY + rand() % 90;
				case 6: pEnt->GetEyeAngles2()->y = 180 + rand() % 90;
				case 7: pEnt->GetEyeAngles2()->y = oldLBY + pEnt->GetEyeAngles2()->y + rand() % 45;
				case 8: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw(); break;
				case 9: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 90; break;
				case 10: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 180; break;
				case 11: pEnt->GetEyeAngles2()->y = oldLBY + rand() % 45; break;
				case 12: pEnt->GetEyeAngles2()->y = pEnt->GetLowerBodyYaw() + rand() % 90; break;
				case 13: pEnt->GetEyeAngles2()->y = pEnt->GetEyeAngles2()->y + rand() % 360; break;
				}
			}
		}
	}
}



int CResolver::vhociaqqdoxorf(string umdnnzvoox) {
	double wdkmalrxf = 36919;
	double sairddjwe = 33627;
	int jheojrft = 6449;
	string wrqnvwwp = "nehmzenhtntcsrrmzxhjkhsdh";
	int djajk = 372;
	if (372 == 372) {
		int sinz;
		for (sinz = 29; sinz > 0; sinz--) {
			continue;
		}
	}
	if (6449 == 6449) {
		int epyehqt;
		for (epyehqt = 44; epyehqt > 0; epyehqt--) {
			continue;
		}
	}
	if (372 == 372) {
		int ipx;
		for (ipx = 61; ipx > 0; ipx--) {
			continue;
		}
	}
	if (6449 == 6449) {
		int oktyht;
		for (oktyht = 69; oktyht > 0; oktyht--) {
			continue;
		}
	}
	if (372 == 372) {
		int vzcehoo;
		for (vzcehoo = 25; vzcehoo > 0; vzcehoo--) {
			continue;
		}
	}
	return 30795;
}

double CResolver::pzhltfoitnh(double eknmgk, int hkxfeczecxcjoy) {
	bool cdsmpdextizko = true;
	string dvlmeqgfghm = "ixbtadotofdeurdslfhmdyte";
	string dzmydbvmzhmuir = "pmripjcpfkyneyshhhrvkfqkebftexyzjaommmbrboqpprjwfbsmqywkoqqjidaoox";
	double flbxbozlotfroc = 12425;
	double dymtcfadfc = 58209;
	int gebkiali = 2841;
	string izeudpohxvfx = "zyluefarehutwcnamgxcunfnkwukxfcbhfrsfwujfjknmvymusjnhquxltigjuvztpqzhlhunnjcwzw";
	int ltrsdtymeblbr = 561;
	string pekai = "odwxuvmlwuwasxnuhgvwafkaccsqtn";
	if (true == true) {
		int pvzajibku;
		for (pvzajibku = 97; pvzajibku > 0; pvzajibku--) {
			continue;
		}
	}
	return 54117;
}

void CResolver::tgzhdizmnyg(int ohvyz, bool jgjwsoq, string usalmpalgg, int ctllvwodosxeqz) {
	double psmkswks = 46213;
	bool nsgkgsljthhsdmr = false;
	int zkorhkkt = 634;
	bool hhgoslzybpl = true;
	int traukfhnjizxvt = 6515;
	int vrqdbwsx = 676;
	bool dxmsypuydlpofrb = true;
	string aemasxnqzpp = "xdepfbprsivoeszrsopwnmjlnfqzmjbhbhpocdyzduvmwchocwnnqkhgsmioymtgvqaxwl";
	string tuftnpoc = "rwoxfmnizpwzlbmogmwpzahlsuyhfnnswlffaojlajqicajovqatjdaguvdtlpbirzjo";
	int qlejws = 3686;
	if (3686 == 3686) {
		int az;
		for (az = 35; az > 0; az--) {
			continue;
		}
	}
	if (6515 == 6515) {
		int bvw;
		for (bvw = 44; bvw > 0; bvw--) {
			continue;
		}
	}
	if (46213 == 46213) {
		int xnvdxcjt;
		for (xnvdxcjt = 76; xnvdxcjt > 0; xnvdxcjt--) {
			continue;
		}
	}

}

string CResolver::ixhxwxdrjnlgtqpbacteekz(bool azdamfdgsnkgsll, string ghkabldii, int nohtnwkrftlnez, string hizdbl, double grtkkkjgc, int ubnji, int ditmnrdd, bool jhborjtfcbvecg, double sieymhposu) {
	int lnyaofgvng = 3034;
	string zuwqmkiciibpz = "nkvwwswzcvsbjvsazbqmxd";
	int fnsokmvgvjrffg = 1303;
	if (3034 != 3034) {
		int hf;
		for (hf = 52; hf > 0; hf--) {
			continue;
		}
	}
	return string("u");
}

int CResolver::kqlazaoikstrymppnbwavz(double fjhomslqzqnqv, bool pxwzfxg, int hloyik, int uopwhmiyr, bool zelblkppu, string komynrhvgx, int kirrpjenwrvn, double uxmwomplvkr, double xcrkkwqkmvhhr, bool ddfcqzgdwyqckq) {
	int gvyieb = 486;
	double kyjeza = 13006;
	int ffmqjwkkift = 1867;
	double kfiilxdrm = 22198;
	string jzaidkn = "rfyrdroduukmxxyfpykwxzkpjntvxgavkexgrsmygunnklgagcxuuzwnrjacdqu";
	if (22198 != 22198) {
		int eznhbnvr;
		for (eznhbnvr = 49; eznhbnvr > 0; eznhbnvr--) {
			continue;
		}
	}
	return 93393;
}

void CResolver::cxtrewxncrvudoqafdd(double hxrvxc, bool rwvoqdpgucqrili) {
	bool wnuddtyavbuci = true;
	bool gckkupoj = false;
	double tcrsrhznlnbosyr = 25890;
	if (false != false) {
		int xzrpahjky;
		for (xzrpahjky = 72; xzrpahjky > 0; xzrpahjky--) {
			continue;
		}
	}

}

string CResolver::lbxfdnobjtzoikinpynzqxbht(int sjqposjpi, string bnvpddgvdqqwfn, bool uoetdyfr, string orqpoqkc, bool bxczlqrrv, double lydlqeygyvmnn, int rkolikgvf, int iigrmvzslav) {
	double wbbdmggqnfyvvl = 30447;
	string mjtjfspa = "xwfwdlwncqjervujxhrcepduvqectdaw";
	int amrlnrc = 577;
	int tskqqiohlzuvbcm = 5159;
	bool wtnzqdyxngrz = true;
	double ymjiynn = 761;
	double wllpwr = 57372;
	bool pczdybtiv = true;
	if (761 == 761) {
		int bsrmrhdxj;
		for (bsrmrhdxj = 40; bsrmrhdxj > 0; bsrmrhdxj--) {
			continue;
		}
	}
	if (true != true) {
		int rltrjhnjr;
		for (rltrjhnjr = 88; rltrjhnjr > 0; rltrjhnjr--) {
			continue;
		}
	}
	if (761 != 761) {
		int wniw;
		for (wniw = 8; wniw > 0; wniw--) {
			continue;
		}
	}
	if (30447 == 30447) {
		int poikhknyh;
		for (poikhknyh = 43; poikhknyh > 0; poikhknyh--) {
			continue;
		}
	}
	return string("kmbrfyrzqma");
}

string CResolver::hcrreeohprgfenqzjynaia(string rcwkwbwjxb, double asjzzczqwdtqlq, int prbwjasmupeaqyu) {
	int oflcxoyjhtwfgyp = 1169;
	if (1169 != 1169) {
		int cbv;
		for (cbv = 24; cbv > 0; cbv--) {
			continue;
		}
	}
	if (1169 == 1169) {
		int lpiyllq;
		for (lpiyllq = 65; lpiyllq > 0; lpiyllq--) {
			continue;
		}
	}
	return string("sdiy");
}

double CResolver::exinkghhrgjz(int xpzvlreg, double paibaxhbhgmoz) {
	int zibmhwyd = 992;
	int pdzsolwbybj = 902;
	bool wlzsousbffets = true;
	int wuctqanbyamkiur = 4004;
	double jyxapyb = 31320;
	if (902 == 902) {
		int ylbe;
		for (ylbe = 95; ylbe > 0; ylbe--) {
			continue;
		}
	}
	return 18343;
}

int CResolver::davkxspzll(double axepqvvfbktnnw, bool muwpakcq) {
	string dfllttdf = "nfbuwgefnyumljpmptkjocnbmqvuwidleqeqhyvyjuhgmaygbbwkackuxqsayayrrhwgwjpvzuonqqfkjkkhrtxutmbcthfbebpq";
	double yejxj = 2582;
	int neuedtcayrr = 1512;
	if (1512 != 1512) {
		int vidpg;
		for (vidpg = 11; vidpg > 0; vidpg--) {
			continue;
		}
	}
	if (2582 != 2582) {
		int qybsewu;
		for (qybsewu = 67; qybsewu > 0; qybsewu--) {
			continue;
		}
	}
	return 45204;
}

int CResolver::lpqssgzfwgceer(int gkrgznckf, double tpburrrwo, string bvecjgcefqa, string rhkczlshbnlm, int uqldaywfru, double yhkvkg, bool jsgziupaq, double nfyvpkppkqmbe, int lkhpsdpsq) {
	return 70204;
}

bool CResolver::bxhsheykiqubeczbfvqresgf(double gsorviayrhuwf, double awbhfhropmnjijp, string fksfovz, bool ygmwvglup) {
	double ckibhxb = 1589;
	string bhdupnhlswjou = "foetortetceetbctkdgtmsikpnmtyrdbwxnbctxcatjjanmiqlabvlttpcerjcvbdnfnprjupoufanewhbxluauodusw";
	int flxdqauwyr = 561;
	int rkpcbgxejai = 1670;
	int nhzrdxynk = 1438;
	bool koinambmicvxnr = true;
	if (1438 == 1438) {
		int ao;
		for (ao = 84; ao > 0; ao--) {
			continue;
		}
	}
	if (561 == 561) {
		int ku;
		for (ku = 95; ku > 0; ku--) {
			continue;
		}
	}
	return true;
}

double CResolver::tngjdiqfbw(string tkxixlbhjflu, int rhwhfp, double vnpzjr, bool bklqzwfrq, int bhcvq, double mchfca, int bgwisloaktsbmug, bool kipixzolcs, string sntea, int vzitipnijhnha) {
	string zrijisoyi = "ykwbvhjujcywehqehzatredrkahfwictvkuaeqtnkvedz";
	bool fbycektzsa = false;
	bool dxjdbaebxgmu = true;
	bool hdbuktbrmatrhf = true;
	if (true != true) {
		int gyceb;
		for (gyceb = 14; gyceb > 0; gyceb--) {
			continue;
		}
	}
	if (false != false) {
		int nieedfnnu;
		for (nieedfnnu = 40; nieedfnnu > 0; nieedfnnu--) {
			continue;
		}
	}
	if (string("ykwbvhjujcywehqehzatredrkahfwictvkuaeqtnkvedz") != string("ykwbvhjujcywehqehzatredrkahfwictvkuaeqtnkvedz")) {
		int bbkpih;
		for (bbkpih = 45; bbkpih > 0; bbkpih--) {
			continue;
		}
	}
	if (true != true) {
		int dobwfxhl;
		for (dobwfxhl = 47; dobwfxhl > 0; dobwfxhl--) {
			continue;
		}
	}
	return 80643;
}

bool CResolver::wvdjxxivuq() {
	double wuecgjqkg = 47975;
	bool xbqoxq = false;
	double bgwnv = 10418;
	double aabjxv = 76895;
	int nyftqe = 965;
	if (47975 != 47975) {
		int tposdmusf;
		for (tposdmusf = 79; tposdmusf > 0; tposdmusf--) {
			continue;
		}
	}
	if (76895 == 76895) {
		int ta;
		for (ta = 62; ta > 0; ta--) {
			continue;
		}
	}
	return true;
}

string CResolver::ztuwzcuhgkwdobmpwyytylh(bool uqydfcdspjo, string fygluatplaeemoe, double epwvb, string wpilgzjlt, string ldyscnyro, string zyancllyrgf, bool pmfunrhhptrzltq, int wnpeczsqblvibz, int vxfoyyaxlxxwxvu) {
	double jiwqnvxali = 25568;
	int vveziiqwlp = 2400;
	if (25568 == 25568) {
		int ymbbhtf;
		for (ymbbhtf = 37; ymbbhtf > 0; ymbbhtf--) {
			continue;
		}
	}
	if (25568 != 25568) {
		int xvet;
		for (xvet = 1; xvet > 0; xvet--) {
			continue;
		}
	}
	return string("d");
}

string CResolver::deptkhpcmvewcxuwhttyrtby(string djhkuqsfc, string fgkuavtfvlbba, bool epnvofgmz, string wucofkpeyfmfb, bool wnayhjdjqjbt, bool fbhqpbwehj, double ukovjxo, string nlhhdvutmovbvz, int qkuxzr) {
	int dvykinf = 943;
	bool jzfsadervx = true;
	double ncpwcvis = 35843;
	int mfiolhwzycxw = 4857;
	double qrxrdygzmmzl = 39566;
	if (39566 != 39566) {
		int kij;
		for (kij = 95; kij > 0; kij--) {
			continue;
		}
	}
	return string("ps");
}
