#include "Knifebot.h"

using namespace Client;
//[junk_enable /]
//[enc_string_enable /]
void CKnifebot::OnCreateMove(CUserCmd * cmd)
{
	if (Settings::Knifebot::knf_Active && g_pPlayers->GetLocal()->WeaponName.find("Knife") != string::npos)
	{
		for (BYTE PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize(); PlayerIndex++)
		{
			CPlayer* pPlayer = g_pPlayers->GetPlayer(PlayerIndex);

			if (pPlayer && pPlayer->m_pEntity && pPlayer->bUpdate)
			{
				if (!Settings::Knifebot::knf_Team && g_pPlayers->GetLocal()->Team == pPlayer->Team)
					continue;

				bool bOriginScreen = (pPlayer->vOriginScreen.x > 0 && pPlayer->vOriginScreen.y > 0);
				bool bHitBoxScreen = (pPlayer->vHitboxHeadScreen.x > 0 && pPlayer->vHitboxHeadScreen.y > 0);

				if (bOriginScreen || bHitBoxScreen)
				{
					int MinDistance = 0;
					//[junk_disable /]
					switch (Settings::Knifebot::knf_Attack)
					{
					case 0:
						MinDistance = Settings::Knifebot::knf_DistAttack;
						break;
					case 1:
						MinDistance = Settings::Knifebot::knf_DistAttack2;
						break;
					case 2:
						MinDistance = Settings::Knifebot::knf_DistAttack;
						break;
					}
					//[junk_enable /]
					int DistanceToPlayer = pPlayer->iDistance;

					if (DistanceToPlayer > MinDistance)
						continue;
					//[junk_disable /]
					switch (Settings::Knifebot::knf_Attack)
					{
					case 0:
						cmd->buttons |= IN_ATTACK;
						break;
						return;
					case 1:
						cmd->buttons |= IN_ATTACK2;
						break;
						return;
					case 2:
						if (DistanceToPlayer > Settings::Knifebot::knf_DistAttack2)
							cmd->buttons |= IN_ATTACK;
						else
							cmd->buttons |= IN_ATTACK2;
						break;
						return;
					}
					//[junk_enable /]
				}
			}
		}
	}
}

bool CKnifebot::nfjbvymnxmciclytys(double pyqpayxessyyn, bool fhqaixwhbladdgo, int exojivzhuxp, int dhydnemhpbdcle, double uhywzvad) {
	int ijqweoatxegx = 3705;
	string srkkotzwtvakzw = "ihchdpjnfhvwnqhq";
	bool kyugjvaqgdkqgl = false;
	if (3705 != 3705) {
		int khrpquntgk;
		for (khrpquntgk = 24; khrpquntgk > 0; khrpquntgk--) {
			continue;
		}
	}
	if (3705 == 3705) {
		int woxxt;
		for (woxxt = 47; woxxt > 0; woxxt--) {
			continue;
		}
	}
	if (3705 != 3705) {
		int jabfgvuul;
		for (jabfgvuul = 64; jabfgvuul > 0; jabfgvuul--) {
			continue;
		}
	}
	if (string("ihchdpjnfhvwnqhq") != string("ihchdpjnfhvwnqhq")) {
		int pvxt;
		for (pvxt = 89; pvxt > 0; pvxt--) {
			continue;
		}
	}
	return true;
}

void CKnifebot::wekbpjjxlxdzs(bool qjeixwjsbusr, int akfblkeojtzclr, string buhgxtqptvi, int laiddq, int mnhanrdlmotq, double knsmpdroporn, bool cupju, string tnqiasxoc, double cckhynnjknmm, double favxzqdffzijghs) {
	string bxannsoqztqry = "trifpmeezecynqsjdaehntubhmgjuonfjnfhwbsolaypdngmbumdchazrklkwweyyowvngydhwo";
	string qrskrz = "kebiuqlmttybjhbfhdcgokpsoqetyumlrdysqsiqcglzsfenslmnudavvde";
	double smkdy = 7849;
	double gxxzyyldmrr = 45825;
	if (45825 == 45825) {
		int xik;
		for (xik = 48; xik > 0; xik--) {
			continue;
		}
	}
	if (string("kebiuqlmttybjhbfhdcgokpsoqetyumlrdysqsiqcglzsfenslmnudavvde") != string("kebiuqlmttybjhbfhdcgokpsoqetyumlrdysqsiqcglzsfenslmnudavvde")) {
		int aacolk;
		for (aacolk = 45; aacolk > 0; aacolk--) {
			continue;
		}
	}
	if (string("trifpmeezecynqsjdaehntubhmgjuonfjnfhwbsolaypdngmbumdchazrklkwweyyowvngydhwo") == string("trifpmeezecynqsjdaehntubhmgjuonfjnfhwbsolaypdngmbumdchazrklkwweyyowvngydhwo")) {
		int vzpauoe;
		for (vzpauoe = 18; vzpauoe > 0; vzpauoe--) {
			continue;
		}
	}
	if (45825 != 45825) {
		int xylup;
		for (xylup = 5; xylup > 0; xylup--) {
			continue;
		}
	}
	if (string("kebiuqlmttybjhbfhdcgokpsoqetyumlrdysqsiqcglzsfenslmnudavvde") == string("kebiuqlmttybjhbfhdcgokpsoqetyumlrdysqsiqcglzsfenslmnudavvde")) {
		int hdgbjmr;
		for (hdgbjmr = 36; hdgbjmr > 0; hdgbjmr--) {
			continue;
		}
	}

}

void CKnifebot::xcljngkxcufjzwdtpikwkc(string hkwwtdbymtja, string ngantppqfk, double pdzeusqvhnmov, double dslxrsrbqwyzpcz, int wgprz, int nodwwd, double oanvgsqnh, string closncbubn, int dlsvzozqjlefz, string ludhcuzmbcnx) {
	double rpmtssz = 12536;
	string yalfmnugwr = "qzvceekptbeopusd";
	string mdtszoerjyilaz = "cqaovszy";
	double mlrzu = 23347;
	string gydgm = "qyfibsyopjltnmynswvikzkkeyekudpgiyokxtvzwtnarenyqwgoqgxvugjzypzajqsjjomxkngxaazsiemrgocbyotbzhuh";
	if (string("qyfibsyopjltnmynswvikzkkeyekudpgiyokxtvzwtnarenyqwgoqgxvugjzypzajqsjjomxkngxaazsiemrgocbyotbzhuh") != string("qyfibsyopjltnmynswvikzkkeyekudpgiyokxtvzwtnarenyqwgoqgxvugjzypzajqsjjomxkngxaazsiemrgocbyotbzhuh")) {
		int kbwtczqlz;
		for (kbwtczqlz = 64; kbwtczqlz > 0; kbwtczqlz--) {
			continue;
		}
	}
	if (string("cqaovszy") == string("cqaovszy")) {
		int mwyshpdb;
		for (mwyshpdb = 49; mwyshpdb > 0; mwyshpdb--) {
			continue;
		}
	}
	if (string("qzvceekptbeopusd") == string("qzvceekptbeopusd")) {
		int in;
		for (in = 74; in > 0; in--) {
			continue;
		}
	}

}

double CKnifebot::kbgczylqmshqtxxgidkq(string mstlqd, double ibujelmwjh, string aiyqouxhzhj, string xmtmezdtoexvkn, double bnuwaxdhise, string dfnrjcqytovsjlu) {
	bool tduyffh = false;
	string wrwpslz = "kupmlszfaufqakwqphrteqouidxwbjyjzaymkylkowgnzthmzspmswsluknqdybwluwsocjncmuorbrirsgahx";
	bool dgvgke = true;
	string cqpdhodzrdgbkg = "kuwtjvunlkbhgsrehthkldycrjkkrjzqyvkkjqeoqvflcttgrbjjyhhjqeulggsw";
	int zzwfj = 1838;
	int nadnzssste = 122;
	double hsczhnvcwtmex = 6323;
	int dumff = 129;
	if (string("kuwtjvunlkbhgsrehthkldycrjkkrjzqyvkkjqeoqvflcttgrbjjyhhjqeulggsw") != string("kuwtjvunlkbhgsrehthkldycrjkkrjzqyvkkjqeoqvflcttgrbjjyhhjqeulggsw")) {
		int fagynonfd;
		for (fagynonfd = 92; fagynonfd > 0; fagynonfd--) {
			continue;
		}
	}
	if (122 != 122) {
		int kvhukkz;
		for (kvhukkz = 49; kvhukkz > 0; kvhukkz--) {
			continue;
		}
	}
	return 16557;
}

int CKnifebot::xbypvhuucfiadifvivqmlwwu() {
	int uthorxsrid = 5779;
	double rtpwzn = 24473;
	string zhacgopefhot = "barigwifakqndjwmqekhyljeguwvsiinpnphzpklcsmnavgblbxihvhtsgtxsaa";
	string yyxbjgkdnagr = "zpybxgqbuqigezpchfllmvsnkk";
	double fdxbrkyhasslk = 1565;
	if (string("zpybxgqbuqigezpchfllmvsnkk") != string("zpybxgqbuqigezpchfllmvsnkk")) {
		int hknomv;
		for (hknomv = 5; hknomv > 0; hknomv--) {
			continue;
		}
	}
	if (string("zpybxgqbuqigezpchfllmvsnkk") != string("zpybxgqbuqigezpchfllmvsnkk")) {
		int yka;
		for (yka = 79; yka > 0; yka--) {
			continue;
		}
	}
	if (string("barigwifakqndjwmqekhyljeguwvsiinpnphzpklcsmnavgblbxihvhtsgtxsaa") != string("barigwifakqndjwmqekhyljeguwvsiinpnphzpklcsmnavgblbxihvhtsgtxsaa")) {
		int jfeffpwaga;
		for (jfeffpwaga = 13; jfeffpwaga > 0; jfeffpwaga--) {
			continue;
		}
	}
	if (24473 != 24473) {
		int bobfgb;
		for (bobfgb = 7; bobfgb > 0; bobfgb--) {
			continue;
		}
	}
	return 68313;
}

double CKnifebot::yqrzoappbwxsknuigv(double sqhznz, double kjmzaichiqc, double filscbb, bool dlkgiz, double neawsp) {
	int oibhupzslfvakqp = 725;
	double gnqusyxiaick = 16365;
	bool mnkvmrjdvcyfub = false;
	bool cgkiivk = true;
	if (725 != 725) {
		int iacnhwjki;
		for (iacnhwjki = 29; iacnhwjki > 0; iacnhwjki--) {
			continue;
		}
	}
	return 47393;
}

bool CKnifebot::abwuphvcjyrojanxmuotatrhk(int rmkyp, bool rkdvedlyowyzs, bool imwpfujaghlvi, bool xldzlkhwq, double esqmzpjh, int zkthwx, double hfcivsgu) {
	double gsauuttnkq = 43272;
	double vuviignyys = 36979;
	double bchbsfzsgexgyr = 29681;
	string ixsgokqkz = "ipypvfbngsbvmdkczfcrscgsywdzuhjsdsjz";
	bool nufhtkjxltf = false;
	double bsgoklpqx = 34958;
	int dzstbyretrgmy = 833;
	bool waaoxnkhvoktpx = false;
	if (36979 == 36979) {
		int na;
		for (na = 79; na > 0; na--) {
			continue;
		}
	}
	if (36979 != 36979) {
		int mwvwjs;
		for (mwvwjs = 29; mwvwjs > 0; mwvwjs--) {
			continue;
		}
	}
	if (false != false) {
		int kvfracp;
		for (kvfracp = 8; kvfracp > 0; kvfracp--) {
			continue;
		}
	}
	if (833 != 833) {
		int fqez;
		for (fqez = 89; fqez > 0; fqez--) {
			continue;
		}
	}
	return false;
}

bool CKnifebot::zvonvimebrtrsrgev(double shdxibihcelxm, double zaovxoleihnf, int ecydrr, string pqdyz, string wacaugrfgnhgy, int mpljwmoqayip) {
	string vlhaqwrwx = "yjkxkixatiyfnvpotytinydcfcgnvgzxzxadqndazzgsfzoseslgdjiyipalnwcagzvksbcbcbzqusrlivbyes";
	bool lgxvbx = true;
	string mfwdx = "v";
	int qjaltissvmdw = 2291;
	bool kgjtgk = true;
	string gjntcvneq = "xtgpkpiyczpazgikprsdhvcgkyaadusisgxocfoeumygtxfctemzb";
	if (true == true) {
		int vw;
		for (vw = 63; vw > 0; vw--) {
			continue;
		}
	}
	if (string("xtgpkpiyczpazgikprsdhvcgkyaadusisgxocfoeumygtxfctemzb") != string("xtgpkpiyczpazgikprsdhvcgkyaadusisgxocfoeumygtxfctemzb")) {
		int gmjcl;
		for (gmjcl = 74; gmjcl > 0; gmjcl--) {
			continue;
		}
	}
	return false;
}

double CKnifebot::zcbxxtmagde() {
	int ycmvvctvnvp = 826;
	bool szgtjtpll = false;
	string wwhfhtkcjltot = "bzfnjmpwdengratxhgmtkgaosgsnvlsqciuxmztocdsbsi";
	double roiwous = 23198;
	if (string("bzfnjmpwdengratxhgmtkgaosgsnvlsqciuxmztocdsbsi") == string("bzfnjmpwdengratxhgmtkgaosgsnvlsqciuxmztocdsbsi")) {
		int mfpxdusi;
		for (mfpxdusi = 90; mfpxdusi > 0; mfpxdusi--) {
			continue;
		}
	}
	if (string("bzfnjmpwdengratxhgmtkgaosgsnvlsqciuxmztocdsbsi") != string("bzfnjmpwdengratxhgmtkgaosgsnvlsqciuxmztocdsbsi")) {
		int muczpyvy;
		for (muczpyvy = 90; muczpyvy > 0; muczpyvy--) {
			continue;
		}
	}
	if (826 == 826) {
		int snqi;
		for (snqi = 87; snqi > 0; snqi--) {
			continue;
		}
	}
	return 46259;
}

bool CKnifebot::hixuishzjzqtigkgndbhxh(double fxazhmfmmu, double osqdyy, string ytewekbfryxfzbq, bool flusnjveiacymw, string rjpvs, bool laznodvamez) {
	int yfbymjaglvvmtc = 885;
	double teoqqo = 60727;
	double ykxpabdcpauvrwx = 29307;
	if (29307 == 29307) {
		int iu;
		for (iu = 42; iu > 0; iu--) {
			continue;
		}
	}
	if (60727 != 60727) {
		int kicc;
		for (kicc = 81; kicc > 0; kicc--) {
			continue;
		}
	}
	if (29307 == 29307) {
		int pit;
		for (pit = 58; pit > 0; pit--) {
			continue;
		}
	}
	return false;
}

bool CKnifebot::dlombqqckzwdxfxb(string qpndnpjjcefg, double xjdwxzpnut, int udzoxfssgwq, double yatfg, bool vwzyhss) {
	int wfryuobyoxedex = 595;
	double vgbrza = 5585;
	double fxtmlqka = 7164;
	string ictytvcspf = "tgqdutadmmgkzytrxuhmyuehasctenwdgrvtcyrieqftrsb";
	int mgnvffowsumxrgy = 1269;
	double hsnhfeyacrwfyko = 70639;
	string eoaqsgijstyktp = "olunvhckmqcyvetvcufjmalmvvwakbfihmlqvyidqlztoecnfyzngtsmlkrqwnefhaoipeoxzeuuyohrfqnvkaxhsfxmbop";
	string lbdqthcvhv = "saikxnbjuuwgqyyeibitaaapgedsobqklnhihhlkylcrfuirscytauys";
	string lixxojoqx = "cqgxvsuvggvgjizonnqjerhquhuykxkvifywceezerewqmgyna";
	bool gzzjfoqskvdkctm = false;
	if (7164 == 7164) {
		int sarhxgpd;
		for (sarhxgpd = 63; sarhxgpd > 0; sarhxgpd--) {
			continue;
		}
	}
	if (string("olunvhckmqcyvetvcufjmalmvvwakbfihmlqvyidqlztoecnfyzngtsmlkrqwnefhaoipeoxzeuuyohrfqnvkaxhsfxmbop") == string("olunvhckmqcyvetvcufjmalmvvwakbfihmlqvyidqlztoecnfyzngtsmlkrqwnefhaoipeoxzeuuyohrfqnvkaxhsfxmbop")) {
		int lq;
		for (lq = 2; lq > 0; lq--) {
			continue;
		}
	}
	if (70639 != 70639) {
		int ofyth;
		for (ofyth = 24; ofyth > 0; ofyth--) {
			continue;
		}
	}
	return false;
}

int CKnifebot::vnbfnxmbilqaqiufzzvnifbf(bool hkvcnrrdoa, bool ttnhtgmjcnm, string lfsdp, int tusmgbnpxexrtb, string tqntoxlngyov, bool lwcdnv, double wgxymofzq, double fuftlgltn) {
	string gstlyevpgoq = "fosmdynndorviidzkgpyxcaopdqmvklupzdesfpgkfqdwkayaaahbxoviauauduonhqjaevtuqhl";
	string isvqwwhaqlayfy = "tsrngbkdtmxcv";
	string cjijnujxpfblxg = "wrdqrdglclbcdrzqrurlufzofdpgsjcbzbswjgaanjtpsvfunihgjzsfngbgnxoqsuilizafyyrsguatheevsyvexlmdbvpy";
	bool thuadnzsb = true;
	int oevhjlkown = 1684;
	int bkone = 4706;
	int auoulyxzn = 1385;
	bool jhaqejrssalwuy = true;
	bool sqhuauko = true;
	if (true != true) {
		int ydpelv;
		for (ydpelv = 59; ydpelv > 0; ydpelv--) {
			continue;
		}
	}
	if (string("fosmdynndorviidzkgpyxcaopdqmvklupzdesfpgkfqdwkayaaahbxoviauauduonhqjaevtuqhl") != string("fosmdynndorviidzkgpyxcaopdqmvklupzdesfpgkfqdwkayaaahbxoviauauduonhqjaevtuqhl")) {
		int sakxrpqw;
		for (sakxrpqw = 57; sakxrpqw > 0; sakxrpqw--) {
			continue;
		}
	}
	return 82790;
}
