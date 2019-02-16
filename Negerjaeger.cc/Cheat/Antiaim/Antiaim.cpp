#include "Antiaim.h"
#pragma warning(disable:4244)

using namespace Client;

CAntiAim::CAntiAim()
{
	CMe* m_pLocal;
}

void  CAntiAim::Glitchwalk(CUserCmd * cmd, bool& bSendPacket)
{
	CBaseEntity* LocalPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());
	if (Settings::Ragebot::glitch_bool)
	{

		static int iChoked = -1;
		iChoked++;

		static bool slowmo;
		slowmo = !slowmo;


		const auto lag = 90;


		if (iChoked < lag)
		{

			bSendPacket = false;
			if (slowmo)
			{
				cmd->tick_count = INT_MAX;
				cmd->command_number += INT_MAX + cmd->tick_count % 2 ? 1 : 0;
				cmd->buttons |= IN_FORWARD;
				cmd->buttons |= IN_LEFT;
				cmd->buttons |= IN_BACK;
				cmd->forwardmove = cmd->sidemove = 0.f;
			}
			else
			{
				bSendPacket = true;
				iChoked = -1;
				Interfaces::GlobalVars()->frametime *= (LocalPlayer->GetVelocity().Length2D()) / 1.2;
				cmd->buttons |= IN_FORWARD;
			}

		}
		else
		{
			if (!bSendPacket)
			{

				if (slowmo)
				{
					cmd->tick_count = INT_MAX;
					cmd->command_number += INT_MAX + cmd->tick_count % 2 ? 1 : 0;
					cmd->buttons |= IN_FORWARD;
					cmd->buttons |= IN_LEFT;
					cmd->buttons |= IN_BACK;
					cmd->forwardmove = cmd->sidemove = 0.f;
				}

			}
			else
			{

				if (slowmo)
				{
					bSendPacket = true;
					iChoked = -1;
					cmd->tick_count = INT_MAX;
					Interfaces::GlobalVars()->frametime *= (LocalPlayer->GetVelocity().Length2D()) / 1.25;
					cmd->buttons |= IN_FORWARD;
				}

			}
		}

	}
}

void CAntiAim::Fakewalk(CUserCmd * cmd, bool& bSendPacket)
{
	CBaseEntity* pPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	if (GetAsyncKeyState(Settings::Ragebot::fakewalk))
	{
		static int chocking = -1;
		chocking++;

		if (chocking < (int)Settings::Ragebot::walkspeed)
		{
			bSendPacket = false;
			cmd->tick_count += 10;
			cmd += 7 + cmd->tick_count % 2 ? 0 : 1;
			cmd->buttons |= g_pPlayers->GetLocal()->m_pEntity->movetype() == IN_BACK;
			cmd->forwardmove = cmd->sidemove = 0.f;
		}
		else
		{
			bSendPacket = true;
			chocking = -1;
			Interfaces::GlobalVars()->frametime *= (pPlayer->GetVelocity().Length2D()) / 1.f;
			cmd->buttons |= g_pPlayers->GetLocal()->m_pEntity->movetype() == IN_FORWARD;
		}
	}
}


void CAntiAim::pnvoprdmhojedfav(int vapmpjiobppo, double cbtwbwhiq, string fdazedyzdv) {
	bool nwhvcwtuetdyl = true;
	int dnojz = 1516;
	bool ivovtmlwenmw = false;
	double yokxknxdz = 32743;
	bool lsptiovixqttja = true;
	int edsxgvng = 6511;
	double ciydb = 69873;
	double blinyypzxii = 34112;
	if (true != true) {
		int aqugneeflu;
		for (aqugneeflu = 63; aqugneeflu > 0; aqugneeflu--) {
			continue;
		}
	}
	if (false == false) {
		int pxnlnvfk;
		for (pxnlnvfk = 66; pxnlnvfk > 0; pxnlnvfk--) {
			continue;
		}
	}
	if (6511 != 6511) {
		int yhylcw;
		for (yhylcw = 71; yhylcw > 0; yhylcw--) {
			continue;
		}
	}
	if (true == true) {
		int eh;
		for (eh = 36; eh > 0; eh--) {
			continue;
		}
	}
	if (true == true) {
		int yo;
		for (yo = 18; yo > 0; yo--) {
			continue;
		}
	}

}

void CAntiAim::xrvirudifikrikmhwhsuiml(string cdotlokhjrvr, string klnigoxodj, bool lesakieh, bool dmiew, double rrotcptjhodb, double srhloccqafkditi, string tvgbtehxjcpc, string jzuvxyor) {
	string qsqjmgfowdba = "uudatikfyk";
	double zyuenzey = 14103;
	double trwjnsgpfhlrkgp = 22352;
	bool fzmvsb = true;
	string fgyemr = "bjavpfpaaqysftivqxqaiqxgihjvkylgxaedqrcilbezuzdzpsuvmlkrwefysqvoeepbbjddwecnvyxlftfgwvemkpc";
	double kglbjylgjoskrs = 49908;
	int bfgmhaxsyea = 34;
	int totusvobqodd = 1110;
	string owxdxbbjy = "spimfykwmpooqoeblqplabsoyukrsjevgmrtmwltufxnmdekdfaainopcgmtfsxeiwhmic";
	bool wbvflnor = true;
	if (22352 == 22352) {
		int zvtw;
		for (zvtw = 94; zvtw > 0; zvtw--) {
			continue;
		}
	}
	if (22352 != 22352) {
		int tbevwva;
		for (tbevwva = 44; tbevwva > 0; tbevwva--) {
			continue;
		}
	}
	if (14103 != 14103) {
		int pc;
		for (pc = 96; pc > 0; pc--) {
			continue;
		}
	}
	if (true == true) {
		int zadbnypvh;
		for (zadbnypvh = 72; zadbnypvh > 0; zadbnypvh--) {
			continue;
		}
	}

}

int CAntiAim::vpervbfuouwkwvhsbsq(int adcyl, double utctdxxfcf, bool dalzzfvjxffwo) {
	double qbukylfv = 7579;
	double mtcsr = 18012;
	bool gzqnhssn = true;
	bool weaxzhmmqlhhhb = true;
	double ojeeydz = 2142;
	bool sekkmcg = true;
	if (7579 == 7579) {
		int yhlt;
		for (yhlt = 80; yhlt > 0; yhlt--) {
			continue;
		}
	}
	if (true != true) {
		int vs;
		for (vs = 40; vs > 0; vs--) {
			continue;
		}
	}
	if (7579 == 7579) {
		int qavgt;
		for (qavgt = 77; qavgt > 0; qavgt--) {
			continue;
		}
	}
	if (7579 != 7579) {
		int yry;
		for (yry = 51; yry > 0; yry--) {
			continue;
		}
	}
	if (2142 == 2142) {
		int zhf;
		for (zhf = 73; zhf > 0; zhf--) {
			continue;
		}
	}
	return 11600;
}

string CAntiAim::rrtwfepuqdxkhytnubhqnql(int jvbzicnmy, string uzvcntgxerhx, int xyuvsnht, bool bydzsfqpfohtfa) {
	double ysijngim = 25561;
	int yiudlmyfompoy = 1370;
	string biiypgtvncvzyq = "ygblndetetagdiuuwmkqpapyecyzpmzisevangcsmrsamgtlithjbizdprlpyzxxu";
	if (string("ygblndetetagdiuuwmkqpapyecyzpmzisevangcsmrsamgtlithjbizdprlpyzxxu") != string("ygblndetetagdiuuwmkqpapyecyzpmzisevangcsmrsamgtlithjbizdprlpyzxxu")) {
		int qv;
		for (qv = 7; qv > 0; qv--) {
			continue;
		}
	}
	if (string("ygblndetetagdiuuwmkqpapyecyzpmzisevangcsmrsamgtlithjbizdprlpyzxxu") != string("ygblndetetagdiuuwmkqpapyecyzpmzisevangcsmrsamgtlithjbizdprlpyzxxu")) {
		int gbphm;
		for (gbphm = 2; gbphm > 0; gbphm--) {
			continue;
		}
	}
	if (25561 != 25561) {
		int bcczwqum;
		for (bcczwqum = 24; bcczwqum > 0; bcczwqum--) {
			continue;
		}
	}
	if (string("ygblndetetagdiuuwmkqpapyecyzpmzisevangcsmrsamgtlithjbizdprlpyzxxu") == string("ygblndetetagdiuuwmkqpapyecyzpmzisevangcsmrsamgtlithjbizdprlpyzxxu")) {
		int efxpr;
		for (efxpr = 4; efxpr > 0; efxpr--) {
			continue;
		}
	}
	return string("udzpz");
}

bool CAntiAim::kzdwarqofasqfwmxzbxqdvdei(int teqkwkc, int stqmxubeaktwfs, double widtrro, string oglysmpxcc, double wreqspddsyyq, int rtsiypcuwnjff, int mkxjnrzirt, bool xtxjbj, int wyzdf, bool utoddtnfpmdcjn) {
	bool mvpgv = true;
	if (true == true) {
		int yvrqmpa;
		for (yvrqmpa = 23; yvrqmpa > 0; yvrqmpa--) {
			continue;
		}
	}
	if (true == true) {
		int isohzfu;
		for (isohzfu = 7; isohzfu > 0; isohzfu--) {
			continue;
		}
	}
	return false;
}

void CAntiAim::byuusthwtlpnjwybpqvcvz(bool oiswbdpjtectoq, bool zuxsyq, string muurfrk, double bzfmjbfqxxxxp, string aayvr, double jacrwewucfs) {
	string ztena = "pwxcakbxxpzhhcokbehlqgxwyntqnbsqhhhefziuzzsojtmlvpaqchghjaopiwxvnzzmnvzbdixpwlazpxnvbprymhfnqhhjs";
	int jjrbj = 60;
	string rywjmqqwrzsjs = "lenbhgicnkspurzgmkkfjiwffgbwgbzzdihlxmqgvjqmgdticekhjcpfelcawiswulaqsvcgucvxmggikpbifhfmkmyz";
	double mzkhsdjehqhw = 33332;
	bool myzalpajihgfxi = false;
	bool ltliv = false;
	int hgsmp = 3326;
	double dzzqsoxvab = 8043;
	string pyadzaananlxsl = "ijjxkmnswtezwtalgrydxpodvuobptrgvlsvyqwtleckawfocr";
	if (3326 != 3326) {
		int ko;
		for (ko = 24; ko > 0; ko--) {
			continue;
		}
	}
	if (string("pwxcakbxxpzhhcokbehlqgxwyntqnbsqhhhefziuzzsojtmlvpaqchghjaopiwxvnzzmnvzbdixpwlazpxnvbprymhfnqhhjs") != string("pwxcakbxxpzhhcokbehlqgxwyntqnbsqhhhefziuzzsojtmlvpaqchghjaopiwxvnzzmnvzbdixpwlazpxnvbprymhfnqhhjs")) {
		int nb;
		for (nb = 14; nb > 0; nb--) {
			continue;
		}
	}
	if (string("pwxcakbxxpzhhcokbehlqgxwyntqnbsqhhhefziuzzsojtmlvpaqchghjaopiwxvnzzmnvzbdixpwlazpxnvbprymhfnqhhjs") != string("pwxcakbxxpzhhcokbehlqgxwyntqnbsqhhhefziuzzsojtmlvpaqchghjaopiwxvnzzmnvzbdixpwlazpxnvbprymhfnqhhjs")) {
		int zrbqryaner;
		for (zrbqryaner = 9; zrbqryaner > 0; zrbqryaner--) {
			continue;
		}
	}
	if (string("pwxcakbxxpzhhcokbehlqgxwyntqnbsqhhhefziuzzsojtmlvpaqchghjaopiwxvnzzmnvzbdixpwlazpxnvbprymhfnqhhjs") != string("pwxcakbxxpzhhcokbehlqgxwyntqnbsqhhhefziuzzsojtmlvpaqchghjaopiwxvnzzmnvzbdixpwlazpxnvbprymhfnqhhjs")) {
		int grwhbwwzs;
		for (grwhbwwzs = 2; grwhbwwzs > 0; grwhbwwzs--) {
			continue;
		}
	}

}

bool CAntiAim::opxdpzyvooagqndiuc(bool vhnsfdghzkwsxn, double cmdvivcdzop, int cpoiebnyxxvks, double bxoaoaqpvmq, bool zcuxwkvunpqhztt, string rwyzf) {
	return true;
}

string CAntiAim::aimjscekihrqthwttbmpvktdx(int pvfzhoolaabwjmv, bool mgoda, string ujbjrtfvodfw, double pjydakjg, double gvkknqbjwq, bool aetltesugmmmme, bool ugzkqgtnm, bool koqumttngwbyqr, int viigzdzjeni) {
	int uixshtsaksjesca = 6926;
	bool uffbsqfvezstvag = true;
	string wdzubnjshmio = "dfgmjfnk";
	string cpuvipqdjfiduwp = "rytldrkr";
	int unhzrvnvre = 459;
	bool ejyssefvdzww = true;
	string wxfgwvuazabvke = "xzjfexlgdienqgfdtrhkblumkmfqsabpiklcusnkgijimqwvfaskcbqmcgeitdsrzfexyjykiuwosbgwhlyv";
	string ujlgluzoairtzg = "ycplnfoauydlgqjndfipxwuksoxidgwefbnsymzdfx";
	double bporwyculdbig = 62250;
	return string("hedlbcwciyta");
}

void CAntiAim::euxipdjhqqtwxttruehq(double rmmfzyfezsuyq, string pznsikwi, int yscxkqgvn, bool idvdytcxay, int qjzuglidkkwct, string suwvyptiwg, int pazja, double xycthnkzlaygvmo, double iuidzsjplpxk, string xzcdqnshq) {
	double ssbfpdtmgfv = 49244;
	double hwvfkibkj = 21859;
	if (49244 != 49244) {
		int wzgjqhw;
		for (wzgjqhw = 92; wzgjqhw > 0; wzgjqhw--) {
			continue;
		}
	}

}

void CAntiAim::gacyfjavyrfuanqijjjfjnnbz(bool xoikfsvmslxt, int bppytowx, bool bptnw) {
	bool uaqrqopwa = true;
	string chsgletjf = "xdtjzrie";
	bool hepekex = false;
	bool nroslzanytgpv = true;
	double sfxwqe = 41022;
	string rccspaooe = "vgkdjkvrj";
	if (true != true) {
		int frio;
		for (frio = 64; frio > 0; frio--) {
			continue;
		}
	}

}

bool CAntiAim::prwpyumeccwjdt(int qlrgiwvndfmpu, string jzdmz, string globgvevmaeyxf, double aawvxmmvx, double sklinub, bool fbzmji, int ecrwlehi, int ocibvtvapo, string mptpoxvin, int mhpmsgdfyy) {
	int vptfmtsrptb = 7262;
	bool gccehvkhqrsz = true;
	double fmtjwthunrzyu = 29757;
	bool cfwgtxip = false;
	string unmnsxphadoh = "ismgyjdmwepmspksifhudpejvsqetslbxtmgsrorbrubgossihyqcikcavxrocqhdxkxltdfde";
	if (string("ismgyjdmwepmspksifhudpejvsqetslbxtmgsrorbrubgossihyqcikcavxrocqhdxkxltdfde") == string("ismgyjdmwepmspksifhudpejvsqetslbxtmgsrorbrubgossihyqcikcavxrocqhdxkxltdfde")) {
		int owb;
		for (owb = 53; owb > 0; owb--) {
			continue;
		}
	}
	if (true == true) {
		int sonxopc;
		for (sonxopc = 14; sonxopc > 0; sonxopc--) {
			continue;
		}
	}
	if (true != true) {
		int ybtlgxjs;
		for (ybtlgxjs = 21; ybtlgxjs > 0; ybtlgxjs--) {
			continue;
		}
	}
	if (true != true) {
		int mxadjxmqu;
		for (mxadjxmqu = 6; mxadjxmqu > 0; mxadjxmqu--) {
			continue;
		}
	}
	if (true == true) {
		int ml;
		for (ml = 13; ml > 0; ml--) {
			continue;
		}
	}
	return true;
}

int CAntiAim::pphydhbikfadsvvalbrpv(double woohfjzo, bool kuziom, double cwepvyhjyjuas, string hxodilh, string bfwcjqixsiklnb, string utohf, string maqhhsmamqu, string blzcjnxoyvgj, string caifgl, string mgwhkuuupamq) {
	int qkmhmobpbjrcnws = 6470;
	bool ojikjrwwqockw = false;
	int dxgxoosmwljgosz = 3570;
	string jowcyu = "mpkrrflchowgdnasdlofjflodblzvtwyfrucdzudfycrfvigfscwfeetdof";
	int vcmaevwthf = 5942;
	double mesxkh = 23663;
	string wgwwrkwroln = "zkcnxjycemsaetarlpurqiopgwypgnihvvysvbvubejpvqlvweqvynyfbfnzoaxgkqpcpjljzmnjowrwcqyctowekfokqxna";
	double mazprrymw = 33900;
	int cfrfuhodjgmp = 505;
	int sqyenhckk = 1459;
	if (5942 != 5942) {
		int uzyimz;
		for (uzyimz = 76; uzyimz > 0; uzyimz--) {
			continue;
		}
	}
	if (3570 != 3570) {
		int eqsv;
		for (eqsv = 61; eqsv > 0; eqsv--) {
			continue;
		}
	}
	if (505 == 505) {
		int odtohkdhnz;
		for (odtohkdhnz = 77; odtohkdhnz > 0; odtohkdhnz--) {
			continue;
		}
	}
	if (6470 == 6470) {
		int zzdbo;
		for (zzdbo = 59; zzdbo > 0; zzdbo--) {
			continue;
		}
	}
	return 89064;
}

double CAntiAim::pfbgsqgfoyacd(int roxkjyf, int mxjoyvfmr, string zxxopv, bool uigyeasoeoks, double bvptwjvfysqdegm, double wwuccfbwmzkuw) {
	int eabvahxnwtiqgra = 5930;
	string mdfdfuswzjrjk = "vwfagnunddkpdhlpkseoxousmndcaxqxzigzmifoedlwcxcsqiabalbvkvpyvvnt";
	string cnyfbsuvyrh = "w";
	double nqpukbdmvouvrr = 22174;
	string rbaxguv = "zfcllwxbkmprpchhmwrjrjmuvwhyzwnbsejwteeocuw";
	bool dsmeklsetffxlz = false;
	string lwdobjawjhee = "qgojbjlnlkfdxakmkbglqhrmcixtesgnjsmosnvqluurgwrrvkrgwstusnymodnwukpoyy";
	string shgvzsj = "trubmcwyvmoidisodjrtylykchzlcsourisjvkrqyugjkxxtwmroifbumcemfl";
	if (5930 != 5930) {
		int akc;
		for (akc = 73; akc > 0; akc--) {
			continue;
		}
	}
	if (false != false) {
		int jrotgmimyg;
		for (jrotgmimyg = 8; jrotgmimyg > 0; jrotgmimyg--) {
			continue;
		}
	}
	if (false == false) {
		int frmznw;
		for (frmznw = 39; frmznw > 0; frmznw--) {
			continue;
		}
	}
	if (string("zfcllwxbkmprpchhmwrjrjmuvwhyzwnbsejwteeocuw") == string("zfcllwxbkmprpchhmwrjrjmuvwhyzwnbsejwteeocuw")) {
		int ruidfnezpg;
		for (ruidfnezpg = 45; ruidfnezpg > 0; ruidfnezpg--) {
			continue;
		}
	}
	if (false != false) {
		int clmnckj;
		for (clmnckj = 51; clmnckj > 0; clmnckj--) {
			continue;
		}
	}
	return 43031;
}

int CAntiAim::lhwucbbwctduwdpniwlnhq(double likwnjrzsphnhni, double ybbtuaxeusmddn) {
	string tzcppezzyuf = "clzgwflixlwpplvimlvetmocdgwwfwvhwrzunn";
	bool hpewyddy = false;
	bool uznqi = true;
	string hpjrqgxt = "nvrvxtfjrmafalkpyekzuxpeytjpeqcgvpsrizsotmoutooqhqpnxqdysrmhilrzxfimhq";
	bool lnzfs = false;
	int kumzajiy = 5440;
	bool aclekzrjqw = false;
	string wavwkgdleersdtf = "mjykbdtlmpsmqkkqqiiybghkfozrwnclnqwbbs";
	bool ubleh = true;
	int wkzdljxmelqxlc = 5745;
	if (false == false) {
		int dnkaqdz;
		for (dnkaqdz = 14; dnkaqdz > 0; dnkaqdz--) {
			continue;
		}
	}
	if (false == false) {
		int leozrcoyvt;
		for (leozrcoyvt = 31; leozrcoyvt > 0; leozrcoyvt--) {
			continue;
		}
	}
	if (false != false) {
		int mqpbn;
		for (mqpbn = 92; mqpbn > 0; mqpbn--) {
			continue;
		}
	}
	if (false != false) {
		int zwsw;
		for (zwsw = 71; zwsw > 0; zwsw--) {
			continue;
		}
	}
	return 72893;
}

int CAntiAim::dvztalqdvwziaijvfyn(double clanwbzsy, double wyozhaydgluoso, double wvfbzqt, int yxqcwwro, bool spiekqep, string slkrxw, string egkkhfhftshgxj, int zpnsznnte, double almufjcytiipsk) {
	double jgbflnakw = 35125;
	bool cnekihhg = false;
	string izrahwtulj = "xdmhdqepcdbvmypkedmlbleneyighakmznstwmjjsyggkipo";
	bool tsyregkixrivier = true;
	string djioxzgvpmydeuy = "cwxzlqoehwzvtcefczfwpcaweztiowpylsthlfaumjxtvfzbxjxcytawvistnseldxghdyuhyuznysbemm";
	double sawukhz = 19532;
	bool bshvtaooalyif = false;
	double dkyowwrulwbowx = 67368;
	string yfqqpsaytghuwj = "zefxrjarmmdhhvciqwkkdamaojnwqwqkpexbhjvsyffgbsgqxvhamelwlyszln";
	double xsodhar = 22072;
	if (false != false) {
		int eaalcdub;
		for (eaalcdub = 22; eaalcdub > 0; eaalcdub--) {
			continue;
		}
	}
	if (false != false) {
		int ikagbjlodf;
		for (ikagbjlodf = 11; ikagbjlodf > 0; ikagbjlodf--) {
			continue;
		}
	}
	if (string("xdmhdqepcdbvmypkedmlbleneyighakmznstwmjjsyggkipo") != string("xdmhdqepcdbvmypkedmlbleneyighakmznstwmjjsyggkipo")) {
		int hxlnvkwwr;
		for (hxlnvkwwr = 18; hxlnvkwwr > 0; hxlnvkwwr--) {
			continue;
		}
	}
	return 40631;
}

bool CAntiAim::smpzxwyngovu(bool bjbooj, string spzeiuicbohatv) {
	int stwecdyscqver = 2929;
	bool hmbwukuuhszxv = true;
	bool iwmcuq = false;
	double denewlalkjlciay = 6828;
	string lxndegbnthdx = "xrewavlqecscbkbbpzowqwrrfhctcnknfeeksrn";
	double wgjtmdypws = 10474;
	double xpeyeixmvqse = 461;
	return false;
}

int CAntiAim::yywuflupsmhrujwwkkwxv(string ewoilknjvll, string omwxzrofmxei, double jdxhpuevedtnqsi, int hmvyuzntfnu, string bebht, bool chinrnfptlld, int bycwarzjwsprwm, int pvforr) {
	bool khwyy = true;
	int slveubtmrm = 1332;
	double zhohrbrt = 6727;
	double aidxlgdrtktbx = 50022;
	string wtfmwv = "cljgtmstfqgapdirjnw";
	int iibumuyca = 5933;
	bool frlyqjvlhxm = true;
	string uvfghetxmbtcz = "ezyvlhbpnqftxzpeawjvxzztudu";
	string tstuerjbawxwr = "vpmxeaewpxrxtvsahxpkuyopkfgzkqnftdzskavnbtqmekunounqjiifqxyficdkgltlgxoacrq";
	int nwjletir = 4218;
	if (5933 != 5933) {
		int nysvjwike;
		for (nysvjwike = 44; nysvjwike > 0; nysvjwike--) {
			continue;
		}
	}
	if (true == true) {
		int tfup;
		for (tfup = 93; tfup > 0; tfup--) {
			continue;
		}
	}
	if (true == true) {
		int jpqkw;
		for (jpqkw = 75; jpqkw > 0; jpqkw--) {
			continue;
		}
	}
	if (50022 != 50022) {
		int px;
		for (px = 91; px > 0; px--) {
			continue;
		}
	}
	if (50022 != 50022) {
		int psdpyauc;
		for (psdpyauc = 11; psdpyauc > 0; psdpyauc--) {
			continue;
		}
	}
	return 5216;
}
