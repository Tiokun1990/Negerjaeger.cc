#include "Fakelag.h"


using namespace Client;


void CFakeLag::Fakelag(CUserCmd * cmd, bool& bSendPacket)
{
	if (Settings::Ragebot::FakeLags <= 0)
		return;

	CBaseEntity* LocalPlayer = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(Interfaces::Engine()->GetLocalPlayer());

	if (!Interfaces::Engine()->IsInGame())
		return;

	if (Settings::Ragebot::FakeLags == 1)
	{
		if (Interfaces::Engine()->IsInGame() && LocalPlayer && IsLocalAlive())
		{
			if (cmd->weaponselect != 0 || cmd->buttons & IN_ATTACK)
			{
				choked = Settings::Ragebot::Fakelag_amt - 1;
			}
			else
			{
				choked = choked > Settings::Ragebot::Fakelag_amt - 1 ? 0 : choked + 1;
				bSendPacket = choked < 1;
			}

		}
	}

	if (Settings::Ragebot::FakeLags == 2) {
		if (ticks >= ticksMax)
		{
			bSendPacket = true;
			ticks = 0;
		}
		else
		{
			bSendPacket = ticks < ticksMax - Settings::Ragebot::Fakelag_amt;
		}
	}
	else if (Settings::Ragebot::FakeLags == 3) { // Switch
		static int FakelagFactor = Settings::Ragebot::Fakelag_amt;
		bSendPacket = 1 ? !(ticks % (FakelagFactor + 1)) : 1;
		if (bSendPacket) {
			FakelagFactor = (rand() % 7) + 6;
		}
	}
	else if (Settings::Ragebot::FakeLags == 4) { // Pulsive

		Vector vel = LocalPlayer->GetVelocity();
		vel.z = 0.0f;

		int f = (int)(ceilf((64.0f / 0.0078125f) / vel.Length()));

		if (Settings::Ragebot::Fakelag_amt > 0)
		{
			if (f > Settings::Ragebot::Fakelag_amt)
				f = Settings::Ragebot::Fakelag_amt;
		}
		else
		{
			if (f > 14)
				f = 14;
		}
		if (f < 1)
			f = 1;

		bSendPacket = 1 ? !(ticks % (f)) : 1;
	}

	ticks++;
}



void CFakeLag::jkwxsiotojlgbywcnjp(int ybcnxzhsio, double tybnzobdyo, bool iwwajtqzhnwb, bool jwbltmuuemwn) {
	bool yjbjarsjouavf = false;
	int wxutkn = 787;
	bool hpeigqh = false;
	if (false != false) {
		int trhhpe;
		for (trhhpe = 93; trhhpe > 0; trhhpe--) {
			continue;
		}
	}
	if (false != false) {
		int vhuqabpc;
		for (vhuqabpc = 73; vhuqabpc > 0; vhuqabpc--) {
			continue;
		}
	}
	if (787 == 787) {
		int yoyjgyeigs;
		for (yoyjgyeigs = 16; yoyjgyeigs > 0; yoyjgyeigs--) {
			continue;
		}
	}
	if (false == false) {
		int oujydtywu;
		for (oujydtywu = 97; oujydtywu > 0; oujydtywu--) {
			continue;
		}
	}

}

bool CFakeLag::imemspncsqnbixmvml(bool leofjzvty, double ivcumfc, int wpwdzrkhxp, string gfbdxgqpz, bool kjbnsyza) {
	int wusqnccsu = 1792;
	if (1792 == 1792) {
		int wlrqw;
		for (wlrqw = 50; wlrqw > 0; wlrqw--) {
			continue;
		}
	}
	if (1792 != 1792) {
		int ivfbcc;
		for (ivfbcc = 74; ivfbcc > 0; ivfbcc--) {
			continue;
		}
	}
	if (1792 == 1792) {
		int fzikzkddjn;
		for (fzikzkddjn = 54; fzikzkddjn > 0; fzikzkddjn--) {
			continue;
		}
	}
	return true;
}

double CFakeLag::ehtdxeydyobfbgdghgil(int sjmwn, bool heztvbnfivsnn, bool lgiow, string lgppbewaexvqdct, string ijcsotzvzfaujo, bool tfcnwzucvrt, double zhxhsktt, int slakvr) {
	bool purfucnxvu = false;
	double ciauzhitvhpii = 11745;
	double cgethibohmo = 7660;
	double qksfri = 92481;
	int xdicydou = 5370;
	if (5370 != 5370) {
		int kgnk;
		for (kgnk = 88; kgnk > 0; kgnk--) {
			continue;
		}
	}
	if (11745 != 11745) {
		int zj;
		for (zj = 69; zj > 0; zj--) {
			continue;
		}
	}
	return 15160;
}

int CFakeLag::tkvhhuspwwia(bool jajxjxusv, int mgplcqvbp, int cnlwzodnvewyi, bool uqdlxdiwvyodrl, int ezgfcdod, int rlvcak, bool vkkzllv, int bwrdunalxo, string nqrpj, int raesxolinrudij) {
	string cqspsiadw = "rvzbinqbumrzxmifgaxcnwjjmraalld";
	bool zrnoruesfk = true;
	int cazsqcwgfhn = 47;
	int larvhzdinh = 5824;
	string aejwv = "yeydqvfnagfaxbwvqrxmwmbumwritnphalnacqdjstgjvlpcedpgtvghntocqvqlhkvzkghdjojtlqywwygpnxwoahok";
	bool vfuuwjbppjcscc = true;
	bool odemxxhosamk = true;
	int phefxhyw = 2853;
	int loggckkp = 2088;
	if (string("rvzbinqbumrzxmifgaxcnwjjmraalld") == string("rvzbinqbumrzxmifgaxcnwjjmraalld")) {
		int ibohkcqiqw;
		for (ibohkcqiqw = 0; ibohkcqiqw > 0; ibohkcqiqw--) {
			continue;
		}
	}
	if (string("rvzbinqbumrzxmifgaxcnwjjmraalld") != string("rvzbinqbumrzxmifgaxcnwjjmraalld")) {
		int vbmb;
		for (vbmb = 88; vbmb > 0; vbmb--) {
			continue;
		}
	}
	if (2853 == 2853) {
		int leexmtnqc;
		for (leexmtnqc = 8; leexmtnqc > 0; leexmtnqc--) {
			continue;
		}
	}
	if (true != true) {
		int bz;
		for (bz = 13; bz > 0; bz--) {
			continue;
		}
	}
	if (5824 != 5824) {
		int kdt;
		for (kdt = 94; kdt > 0; kdt--) {
			continue;
		}
	}
	return 84117;
}

double CFakeLag::eiimwncjbfpxhlcfgzhfzcrty(bool yqfrqxlkpquqsak, bool pfdtewxmulhsxjp, bool txsxjs, string fqtfajvlnc, bool rvefnfbhk, bool efiyzfuf, string bylvlzelmxbxzw, bool agmeohmawcqjpc, bool trvjnd) {
	return 70095;
}

double CFakeLag::henmrqijenubulwi(int fsfejf, string txmfqlqsrhdsa, int hsxdsri, bool fbjgplfm) {
	string nabvkyy = "kpxrhteonuvubyo";
	bool krjsnhinoa = true;
	int boqlebgmfokapm = 1274;
	double dkuhfweohpoatqy = 85084;
	double bprht = 55926;
	string jolrcubkc = "jcijcihbgijrgwnhcudwfbhfgedjobuvvqbgikepubaaprzvqidrdjrvuspnbvdhyphlxbz";
	int oiwabkmrupqhat = 1532;
	bool czspxtxttz = true;
	string xfjzut = "koipzzuturrhznugrm";
	if (true != true) {
		int uhjlllbko;
		for (uhjlllbko = 22; uhjlllbko > 0; uhjlllbko--) {
			continue;
		}
	}
	if (true != true) {
		int hy;
		for (hy = 48; hy > 0; hy--) {
			continue;
		}
	}
	if (85084 == 85084) {
		int uuhmnb;
		for (uuhmnb = 18; uuhmnb > 0; uuhmnb--) {
			continue;
		}
	}
	if (55926 == 55926) {
		int tlpg;
		for (tlpg = 95; tlpg > 0; tlpg--) {
			continue;
		}
	}
	if (string("jcijcihbgijrgwnhcudwfbhfgedjobuvvqbgikepubaaprzvqidrdjrvuspnbvdhyphlxbz") == string("jcijcihbgijrgwnhcudwfbhfgedjobuvvqbgikepubaaprzvqidrdjrvuspnbvdhyphlxbz")) {
		int njchj;
		for (njchj = 90; njchj > 0; njchj--) {
			continue;
		}
	}
	return 7524;
}

string CFakeLag::pklmnxiybz(int dntrszi, int jvvcgbs, int hoklznhn) {
	string mkuqtksnxjznpb = "fibenhdaqrkomwjdozbxwdghjldonupcuctiidhozzaotlyrkzvwifsgvt";
	double manceslpzuf = 54456;
	double fekkubyqkrnnud = 23704;
	string cuzzwteeix = "esshkyjrxzeyekzkckelkqvhuwx";
	if (54456 == 54456) {
		int nagsil;
		for (nagsil = 82; nagsil > 0; nagsil--) {
			continue;
		}
	}
	return string("fqnvpiefogyzqfwfyme");
}

void CFakeLag::ygxmrclopyfvpwtznpi(string dwwpflvd, int qmnnmexn, int ymdudqbq, string evxvjrik, double vfsfhgo, int jslyygshn, string vllyhfcbn) {
	string didvbhjkamuzil = "ojrzehvbxnlcqhynnhqibfegmdsdfsabjeiiggomqanlstroj";
	int uudjamyy = 3235;
	int nautzohuyh = 4547;
	string ajxzca = "abzfcoembseiklgxpvwjopateoenugtmzcdgwgnhhtstnannbltkdfwgdaidczdoxcuuublhwdkqgqicnnjylasnmtysxl";
	int ejcxzombxihypo = 1067;
	double zhgxmphufps = 31443;
	if (string("ojrzehvbxnlcqhynnhqibfegmdsdfsabjeiiggomqanlstroj") == string("ojrzehvbxnlcqhynnhqibfegmdsdfsabjeiiggomqanlstroj")) {
		int craeng;
		for (craeng = 22; craeng > 0; craeng--) {
			continue;
		}
	}
	if (31443 != 31443) {
		int rmrtws;
		for (rmrtws = 99; rmrtws > 0; rmrtws--) {
			continue;
		}
	}

}

string CFakeLag::bzpfyttznyeu(int hnuwf, int aflymnzfwo) {
	int vhirtpqziqopbj = 1413;
	int rfceysrtfkbyb = 3531;
	double rgjljyvr = 8785;
	bool dprpapxnaezwx = false;
	if (3531 != 3531) {
		int nhfbf;
		for (nhfbf = 77; nhfbf > 0; nhfbf--) {
			continue;
		}
	}
	if (3531 != 3531) {
		int qqvbjuj;
		for (qqvbjuj = 19; qqvbjuj > 0; qqvbjuj--) {
			continue;
		}
	}
	if (false != false) {
		int axguzy;
		for (axguzy = 72; axguzy > 0; axguzy--) {
			continue;
		}
	}
	if (8785 == 8785) {
		int plgk;
		for (plgk = 93; plgk > 0; plgk--) {
			continue;
		}
	}
	if (1413 == 1413) {
		int uai;
		for (uai = 61; uai > 0; uai--) {
			continue;
		}
	}
	return string("ujopamtimwxxyzz");
}

bool CFakeLag::pteunzkpaw(double uhtxrnhwvbbc, bool nnznypxnmmgoaex, double nkibkkdnccxv, double edlgwiamcltvtr, string yrbavws) {
	bool cqjmkni = true;
	if (true == true) {
		int dqxud;
		for (dqxud = 2; dqxud > 0; dqxud--) {
			continue;
		}
	}
	if (true != true) {
		int aksxyzhvhi;
		for (aksxyzhvhi = 17; aksxyzhvhi > 0; aksxyzhvhi--) {
			continue;
		}
	}
	if (true == true) {
		int llklsmydgs;
		for (llklsmydgs = 78; llklsmydgs > 0; llklsmydgs--) {
			continue;
		}
	}
	return false;
}

string CFakeLag::jqwnpvweaeienzvcqp(string weqojuttywqxm, int qcxpkdjzldufk, string hwccm, int drrwhrtwvmko, double qcjzdyyalsley, int aeyicdi, int xjoekrhtygg) {
	string ysuimmqtwxhmmy = "vtiwwtyejuqpaxupbhkommgwieaalh";
	bool nxywfsuhcdepih = true;
	string suhppgfl = "lbchcwbcydukdrwuruvwigmtmnfvfygydwazmpqdgkeywhhsoughdoxidkckadzljnunyuciwbzkqdojvoshwz";
	string tjslnax = "hrpncpmaedlixaoatdajokrcbqwjirihvmsonjqzjicehaernmirhbferyxxgvcehmesiudgzrvenxyjtccuxrabrwvhrvark";
	int xokcaaxze = 5324;
	int slrlkctbyuw = 2462;
	double aaauuia = 8281;
	int ptwmpzifat = 2581;
	if (2581 == 2581) {
		int xmac;
		for (xmac = 1; xmac > 0; xmac--) {
			continue;
		}
	}
	if (string("vtiwwtyejuqpaxupbhkommgwieaalh") == string("vtiwwtyejuqpaxupbhkommgwieaalh")) {
		int qccbgf;
		for (qccbgf = 65; qccbgf > 0; qccbgf--) {
			continue;
		}
	}
	if (string("lbchcwbcydukdrwuruvwigmtmnfvfygydwazmpqdgkeywhhsoughdoxidkckadzljnunyuciwbzkqdojvoshwz") != string("lbchcwbcydukdrwuruvwigmtmnfvfygydwazmpqdgkeywhhsoughdoxidkckadzljnunyuciwbzkqdojvoshwz")) {
		int vwocghdukm;
		for (vwocghdukm = 38; vwocghdukm > 0; vwocghdukm--) {
			continue;
		}
	}
	return string("jcucahcnimpwfqwsdic");
}

int CFakeLag::wsprpgjkxnfmapaeml(int jotnddnuvxfynwl, bool kfgystjmhu, int lmzuyhwn, bool uvirchvqggwcsm, int ntomyggllpx, bool hjuiy, bool qqarkngxuqkluo, string tcgygednisseiex, bool diqbbi) {
	double xiqdq = 3382;
	string qsumstsgiithxxg = "vkiobsodryyqabljykhwfpdhesflcaqlqiqlfojhcuxtaxwyfvudiqlktfvxqbynbsfjhoskogglcvsmdvtnamp";
	string upnythvrysf = "ejjproumddvnbxtrzcebtellcdjiurihbygdaohyvztzozwmtqhkbhivtizeajfzikswdyurplsrbmwrtaylbkspckuj";
	bool iyygko = false;
	if (false != false) {
		int qnhczdraro;
		for (qnhczdraro = 95; qnhczdraro > 0; qnhczdraro--) {
			continue;
		}
	}
	if (string("ejjproumddvnbxtrzcebtellcdjiurihbygdaohyvztzozwmtqhkbhivtizeajfzikswdyurplsrbmwrtaylbkspckuj") != string("ejjproumddvnbxtrzcebtellcdjiurihbygdaohyvztzozwmtqhkbhivtizeajfzikswdyurplsrbmwrtaylbkspckuj")) {
		int qskvrff;
		for (qskvrff = 36; qskvrff > 0; qskvrff--) {
			continue;
		}
	}
	if (3382 != 3382) {
		int ouqoqx;
		for (ouqoqx = 4; ouqoqx > 0; ouqoqx--) {
			continue;
		}
	}
	if (3382 != 3382) {
		int avohzjukx;
		for (avohzjukx = 69; avohzjukx > 0; avohzjukx--) {
			continue;
		}
	}
	return 16737;
}

void CFakeLag::wnrkyuchjckeywtvxjpovbus(double gsuoieknkdbo, int sxktefs, int conefdsys) {
	int cvoibyrrttigco = 2826;
	double sgbjjknn = 6364;
	string pmofc = "hykyuhxgwo";
	string pgeqgutqe = "owzvyykkeecrliublrndnqyixbxdzjwblgddrlnuzqxsevnicoqpycmhjzbiwdscarnyiqfxgdcknezh";
	if (string("owzvyykkeecrliublrndnqyixbxdzjwblgddrlnuzqxsevnicoqpycmhjzbiwdscarnyiqfxgdcknezh") != string("owzvyykkeecrliublrndnqyixbxdzjwblgddrlnuzqxsevnicoqpycmhjzbiwdscarnyiqfxgdcknezh")) {
		int nfmzhpzb;
		for (nfmzhpzb = 92; nfmzhpzb > 0; nfmzhpzb--) {
			continue;
		}
	}

}

bool CFakeLag::iwzforgcbkxelxumbzwxyzjev() {
	double ojofr = 27717;
	string pyokkkmg = "cwknhstfpqxktucnpyqqfky";
	bool yrwewqojhmygp = true;
	bool hihmfsepv = false;
	int znulcai = 1544;
	bool dxkcdzl = true;
	bool yobzvx = false;
	double gxbqalu = 21345;
	double axcdsmyr = 14586;
	if (14586 == 14586) {
		int bharged;
		for (bharged = 66; bharged > 0; bharged--) {
			continue;
		}
	}
	if (true == true) {
		int stzqwh;
		for (stzqwh = 79; stzqwh > 0; stzqwh--) {
			continue;
		}
	}
	return true;
}

double CFakeLag::xvlrqtrdkjeerr(string yuwiu, bool murjukzzyzj, bool evtraos, string gqvxbmyo, int wzhsnwvclz, double pctvjwbvgiqsgs, double vbjiexfidmsde, bool iyzcyrppwup, string ifeabw) {
	string hmdmcw = "fqzfxhuriagptcwglrayedqotobcpgfq";
	string pdqnn = "kmlxagabsqeuwfyuerpcdkjghpyzxhsjryhdzarnnbuwczujvvg";
	double fhcltpk = 16051;
	if (string("fqzfxhuriagptcwglrayedqotobcpgfq") != string("fqzfxhuriagptcwglrayedqotobcpgfq")) {
		int wjwi;
		for (wjwi = 5; wjwi > 0; wjwi--) {
			continue;
		}
	}
	if (string("kmlxagabsqeuwfyuerpcdkjghpyzxhsjryhdzarnnbuwczujvvg") != string("kmlxagabsqeuwfyuerpcdkjghpyzxhsjryhdzarnnbuwczujvvg")) {
		int uf;
		for (uf = 36; uf > 0; uf--) {
			continue;
		}
	}
	return 1276;
}

double CFakeLag::ntptrktjeswzmqbgzfq(double dcilgwnm, string mffmisaer, bool vmtbawfgh, bool oduzih, double ijjjeot, double fspsfolggasloa, bool sqasuud, double tayydlc, int kmrdnqrkrv) {
	string nlehalonkmmknoc = "viizchgcw";
	bool rbqfqlruwibii = false;
	double ngfetphuzafks = 68997;
	string ggnqcsyiemvizv = "cglmodsvcaebcjnlqxixkkluhbidxzgilhtouqdsvsccjrdqphgwkyoyixfvmkjjzukdylfahmeacogzp";
	double ggpigdoblmdwav = 334;
	int kyiyfaypikx = 5618;
	bool rqbvlojqghfaor = true;
	return 63372;
}

string CFakeLag::wqyruhmfyqiqblof(double tozrutynxjjgg, string owbhzxgsznfgdjx, int yyliogfdjmnm, double bkcayxs, double brrtjjthy) {
	int tzvtpxvwyz = 2872;
	bool azqwmzdq = true;
	string xqnzaoquj = "sesyvdoybrxhgvffzcadfujgobcjacrgimoyfiyvjurfkjowbn";
	int kmhqndcxsw = 2661;
	if (true != true) {
		int qqfnsgxtv;
		for (qqfnsgxtv = 72; qqfnsgxtv > 0; qqfnsgxtv--) {
			continue;
		}
	}
	if (string("sesyvdoybrxhgvffzcadfujgobcjacrgimoyfiyvjurfkjowbn") == string("sesyvdoybrxhgvffzcadfujgobcjacrgimoyfiyvjurfkjowbn")) {
		int tqq;
		for (tqq = 71; tqq > 0; tqq--) {
			continue;
		}
	}
	return string("zec");
}

bool CFakeLag::riklltvbezn(double srvfk, double wbkjhtgzpixofs, int tdatgezqknpley) {
	int frynprvlepjkmu = 6885;
	bool ohwnhmvi = true;
	double krhamapasxhmwc = 26658;
	int mauiuxuhc = 879;
	string yycuab = "evpgbxlknumfhygggcbpyjhmuhkkpozgscrnajgfejddxncl";
	double spftgstjhrnqa = 37739;
	string faibrqdja = "oggnuuqaevfjqlltqvaqnulfyqnuhavxgcv";
	bool oyqhfoqnqouc = false;
	int wkbriwmscijtep = 1737;
	double fgohiqhilnjhl = 26519;
	return false;
}

string CFakeLag::woucaposxkrh(string pslqsgyiiotijq) {
	string xyinwisb = "kvszlhyowvbkaosjzhxymlgwfgkkfgmrmmemelfrxkwsqbbrxpzozdfpblnpukdru";
	if (string("kvszlhyowvbkaosjzhxymlgwfgkkfgmrmmemelfrxkwsqbbrxpzozdfpblnpukdru") == string("kvszlhyowvbkaosjzhxymlgwfgkkfgmrmmemelfrxkwsqbbrxpzozdfpblnpukdru")) {
		int urna;
		for (urna = 46; urna > 0; urna--) {
			continue;
		}
	}
	return string("dpurzw");
}

void CFakeLag::ymcwamvnjv(bool bdizabz, bool qxhvgvfnmdg, double wmriuupzkke, int kykycqqdgbpzkvh, string krsmnmnaeupby, string urvyzlcsbwb, bool wtmhwvqv, bool bzuayytp, int cydbaos, string czubsbgbvmckwr) {

}
