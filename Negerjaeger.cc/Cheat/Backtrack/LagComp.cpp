#include "LagComp.h"
using namespace SDK;
void BackTrack::Update(int tick_count)
{
	latest_tick = tick_count;
	for (int i = 0; i < 64; i++)
	{
		UpdateRecord(i);
	}
}

bool BackTrack::IsTickValid(int tick)
{
	int delta = latest_tick - tick;
	float deltaTime = delta * Interfaces::GlobalVars()->interval_per_tick;
	return (fabs(deltaTime) <= 0.2f);
}

void BackTrack::UpdateRecord(int i)
{
	CBaseEntity* pEntity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);
	if (pEntity && !pEntity->IsDead()/*&& !pEntity->IsDormant()*/)
	{
		float lby = pEntity->GetLowerBodyYaw();
		if (lby != records[i].lby)
		{
			records[i].tick_count = latest_tick;
			records[i].lby = lby;
			records[i].headPosition = pEntity->GetHitboxPosition(0);
		}
	}
	else
	{
		records[i].tick_count = 0;
	}
}

bool BackTrack::RunLBYBackTrack(int i, CUserCmd* cmd, Vector& aimPoint)
{
	if (IsTickValid(records[i].tick_count))
	{
		aimPoint = records[i].headPosition;
		cmd->tick_count = records[i].tick_count;
		return true;
	}
	return false;
}

void BackTrack::legitBackTrack(CUserCmd* cmd)
{
	if (Settings::Aimbot::aim_Backtrack)
	{
		int bestTargetIndex = -1;
		float bestFov = FLT_MAX;
		CBaseEntity* pLocal = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
		PlayerInfo info;
		if (pLocal->IsDead())
			return;

		for (int i = 0; i < Interfaces::Engine()->GetMaxClients(); i++)
		{
			auto entity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(i);

			if (!entity || !pLocal)
				continue;

			if (entity == pLocal)
				continue;

			if (!Interfaces::Engine()->GetPlayerInfo(i, &info))
				continue;

			/*if (entity->IsDormant())
				continue;*/

			if (entity->GetTeam() == pLocal->GetTeam())
				continue;

			if (!entity->IsDead())
			{

				float simtime = entity->GetSimTime();
				Vector hitboxPos = entity->GetHitboxPosition(0);

				headPositions[i][cmd->command_number % Settings::Aimbot::aim_Backtracktickrate] = backtrackData{ simtime, hitboxPos };
				Vector ViewDir = angle_vector(cmd->viewangles + (pLocal->GetAimPunchAngle() * 2.f));
				float FOVDistance = distance_point_to_line(hitboxPos, pLocal->GetEyePosition(), ViewDir);

				if (bestFov > FOVDistance)
				{
					bestFov = FOVDistance;
					bestTargetIndex = i;
				}
			}
		}

		float bestTargetSimTime;
		if (bestTargetIndex != -1)
		{
			float tempFloat = FLT_MAX;
			Vector ViewDir = angle_vector(cmd->viewangles + (pLocal->GetAimPunchAngle() * 2.f));
			for (int t = 0; t < Settings::Aimbot::aim_Backtracktickrate; ++t)
			{
				float tempFOVDistance = distance_point_to_line(headPositions[bestTargetIndex][t].hitboxPos, pLocal->GetEyePosition(), ViewDir);
				if (tempFloat > tempFOVDistance && headPositions[bestTargetIndex][t].simtime > pLocal->GetSimTime() - 1)
				{
					tempFloat = tempFOVDistance;
					bestTargetSimTime = headPositions[bestTargetIndex][t].simtime;
				}
			}

			cmd->tick_count = TIME_TO_TICKS(bestTargetSimTime);
		}
	}
}

BackTrack* backtracking = new BackTrack();
backtrackData headPositions[64][25]; //support for 128tick servers


string BackTrack::sfbaghlepwucmtbgzsapus(bool ybdvzcftdyurra, bool qvggzdc, int byzvjociyohxb, bool ofyvmjhkdd, double nrcer) {
	string qfdzbeertyso = "rioldnlqyepsfnhbcdeppplfbmsxvzflfnmvyiopqoxhfmiuudyvhsxwspcaiirjzeammobkmmfsvtppnegpjxnoap";
	int czxzazhfmniz = 2892;
	string jvhqnrvhrnbkxvu = "jdbbuyugihhcifixmlkqtvn";
	int mtureziccduc = 1235;
	return string("umma");
}

string BackTrack::uhrfknlxvakewadlhfpmeuxg(double bjciiogkyhzgr, string syvgahgyxeqjkor) {
	string hwozatfuspd = "lbsaiisnfxekhrhxqabeblnqjkgrbowjxnedce";
	double vpuvbmxyby = 2932;
	if (2932 == 2932) {
		int ble;
		for (ble = 46; ble > 0; ble--) {
			continue;
		}
	}
	if (2932 == 2932) {
		int iozq;
		for (iozq = 3; iozq > 0; iozq--) {
			continue;
		}
	}
	if (string("lbsaiisnfxekhrhxqabeblnqjkgrbowjxnedce") == string("lbsaiisnfxekhrhxqabeblnqjkgrbowjxnedce")) {
		int abhhgorq;
		for (abhhgorq = 77; abhhgorq > 0; abhhgorq--) {
			continue;
		}
	}
	if (2932 == 2932) {
		int qvt;
		for (qvt = 75; qvt > 0; qvt--) {
			continue;
		}
	}
	if (2932 != 2932) {
		int zcw;
		for (zcw = 66; zcw > 0; zcw--) {
			continue;
		}
	}
	return string("azcabmox");
}

int BackTrack::bmuybkcfefetjgrn(int unqntjl) {
	double rxnqwsdxhkvoh = 6372;
	double bavabahpuqxgjo = 16577;
	string rxhkskscfmlawzn = "exaaywitdqvrlfjojizbeikvfrodiboukouxcqcczuunhrjswsfjnilvmlcynitztruxwypydmtqgtsi";
	double avwphprbup = 32579;
	bool fnygmww = false;
	string vytghjlblb = "rlsgvmqdcdgjaqqmdnthgzegnbalopgiqcvfxsisprpmidsoneevngumpczrugijtsafzuhgcjkgslej";
	bool cgbvxwfyeu = true;
	bool poztpkvyygmgkj = false;
	return 21727;
}

double BackTrack::hvderfjerdkhijidrobzipqe(int sxriu, double qmzwfvpjc, int rpcqrukxxo, bool oysst, int xowrtuchvqqq, double atymkorkxg, double dsyosaroszybzyp, double bqoiofkqsjwgjxv, int qvwspxzhmmxkds, int avolckgce) {
	return 88574;
}

void BackTrack::umtjlgkomjxbuvpwl(int edmgsh, bool asqmjmtftkfkp) {
	bool bcpjjfkemgainph = false;
	if (false != false) {
		int epbsbxqsm;
		for (epbsbxqsm = 52; epbsbxqsm > 0; epbsbxqsm--) {
			continue;
		}
	}
	if (false == false) {
		int fnixziab;
		for (fnixziab = 44; fnixziab > 0; fnixziab--) {
			continue;
		}
	}
	if (false == false) {
		int ehhw;
		for (ehhw = 69; ehhw > 0; ehhw--) {
			continue;
		}
	}
	if (false != false) {
		int nehovz;
		for (nehovz = 39; nehovz > 0; nehovz--) {
			continue;
		}
	}

}

string BackTrack::drqzzlsxgyllhzmazocpxdt(double ubiejftnffc, bool gtejpiv) {
	bool rtxsfxyfau = false;
	int qdxbimgqp = 1068;
	if (1068 == 1068) {
		int fmetokl;
		for (fmetokl = 97; fmetokl > 0; fmetokl--) {
			continue;
		}
	}
	if (1068 != 1068) {
		int hfbwp;
		for (hfbwp = 4; hfbwp > 0; hfbwp--) {
			continue;
		}
	}
	if (false != false) {
		int rbbo;
		for (rbbo = 99; rbbo > 0; rbbo--) {
			continue;
		}
	}
	return string("pga");
}

void BackTrack::mcrusdqfsaqqudkfhek(string ggotmdzehunybfb, bool jpgivoxx, bool udotkjfek, bool gitryf, int dnzbsazha, bool jwkdluwmk, string kftduj, double kcxozgnarr, string mcesbtztqmo) {
	string sjrpykdoun = "yjeghmneyrafyyvzjumoagoblkkngfciefotazpejfloukkgdtumwapdhkxntezsjmsnnqupshypileltejshaljpjbk";
	int nkyzxpqiboz = 1669;
	int thuzqpsdzojn = 270;
	if (string("yjeghmneyrafyyvzjumoagoblkkngfciefotazpejfloukkgdtumwapdhkxntezsjmsnnqupshypileltejshaljpjbk") != string("yjeghmneyrafyyvzjumoagoblkkngfciefotazpejfloukkgdtumwapdhkxntezsjmsnnqupshypileltejshaljpjbk")) {
		int et;
		for (et = 10; et > 0; et--) {
			continue;
		}
	}
	if (270 == 270) {
		int tmz;
		for (tmz = 81; tmz > 0; tmz--) {
			continue;
		}
	}

}

int BackTrack::lucsgxxjtyamwrb(double fihvndcoytyh, string prbobsqacnpurkj, double emwzktyo, double qvsgmvvfkalv) {
	int pvdksrjdbi = 1570;
	bool gsnqdze = true;
	string ytvhvzxwetlp = "evujswnnhhg";
	double zptbxf = 11508;
	int ypbwtnkyggnu = 998;
	double bahukwkcuuorop = 94671;
	int srwuufsshye = 3285;
	string qoyixiegas = "mlhumcytyxigzbezdusnrdrzzwuikhfgltxvrennchgfbdlmnlrcvlfgttqststflslrgrkjggpoolwkiaodx";
	int spdfnjff = 1186;
	int vlhmrcydkddi = 4428;
	if (string("evujswnnhhg") == string("evujswnnhhg")) {
		int cmkxqgml;
		for (cmkxqgml = 16; cmkxqgml > 0; cmkxqgml--) {
			continue;
		}
	}
	if (998 != 998) {
		int dwsviy;
		for (dwsviy = 4; dwsviy > 0; dwsviy--) {
			continue;
		}
	}
	if (1570 != 1570) {
		int vvhx;
		for (vvhx = 31; vvhx > 0; vvhx--) {
			continue;
		}
	}
	if (string("evujswnnhhg") != string("evujswnnhhg")) {
		int od;
		for (od = 93; od > 0; od--) {
			continue;
		}
	}
	if (1570 != 1570) {
		int madcc;
		for (madcc = 27; madcc > 0; madcc--) {
			continue;
		}
	}
	return 99857;
}

string BackTrack::jvjjtqjpahkwkmhtkurmsxhpr(int ojvcrpdlrc, bool foapzjki, int wsrbkgmbipquq, bool gxqkdasq, double cbduxdn, bool tprwh) {
	string pldwqhesyzpt = "sealydrbmavustqwmriqyffcvaagprhpimnhojhdsoqfptefjjitykbwlgmofhfanlcbmhsv";
	double kihvdtgcyvcpfsb = 3512;
	bool jqgndgdktntemh = true;
	if (3512 != 3512) {
		int wodq;
		for (wodq = 96; wodq > 0; wodq--) {
			continue;
		}
	}
	if (3512 == 3512) {
		int mkmzargn;
		for (mkmzargn = 28; mkmzargn > 0; mkmzargn--) {
			continue;
		}
	}
	return string("ponnmirmeaxt");
}

void BackTrack::vritilhxosubpyaiztfpyb(bool vfmzkiowop, int finjfb, bool ndjfcgxkq, double vxoygrbvndzbgz, string mdrtujhsya, int jijrxqwqmqxzfn, bool plnjelnbevjy, int ebxkokqeaejp) {
	double rpzhudpbaichtp = 95242;
	bool lsbjpatipymm = true;
	double xqlsxzkx = 43200;
	string nhnhw = "vcukgllqtxghjhqlyaplakowvamwthluftazxyzsuclucpgmegogobomxhzqzkzamrejbnkxivyxkjgdwsrb";
	double jjpucd = 8796;
	bool kwzajxedhnqo = true;
	string llrinjvm = "nr";
	int tvfcrtv = 29;
	string qaescpom = "tylshsohneaqsfrmmksgkyxopjoazjduotnslauicdworofscmlcddgzkgbheyxdvjrtyqkcnvdxubvkkyjzhzdghlqeear";
	string nabcycykhkmlybj = "myyrpydhzjxnocuiycrnlxwmfmyafncmocfheebrwuiojykuaqzeufoh";
	if (43200 == 43200) {
		int ndukd;
		for (ndukd = 52; ndukd > 0; ndukd--) {
			continue;
		}
	}

}
