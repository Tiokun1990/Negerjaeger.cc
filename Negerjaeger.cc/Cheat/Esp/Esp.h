#pragma once

#include "../../Engine/Engine.h"
#include "../../SDK/Sounds.h"

#include <algorithm>

#include <Windows.h>
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib") 



#define CHECK_VALID( _v)    0

//FORCEINLINE vec_t DotProduct(const Vector& a, const Vector& b)
//{
//	CHECK_VALID(a);
//	CHECK_VALID(b);
//	return(a.x*b.x + a.y*b.y + a.z*b.z);
//}

namespace Engine
{
	class CBaseEntity;
	class CPlayer;
}

using namespace Engine;

struct Sound_s
{
	ULONGLONG dwTime;
	Vector vOrigin;
};

class CSoundEsp
{
public:
//[swap_lines]
	vector<Sound_s> Sound;

	Color SoundColor;

	CSoundEsp();

	void Update();
	void AddSound( Vector vOrigin );
	void DrawSoundEsp();
	void DrawWave(Vector loc, float radius, Color color);
//[/swap_lines]
};

class CEsp
{
public:

	CEsp();
	void DrawDamageIndicator();
//[swap_lines]
	CSoundEsp SoundEsp;

	Color CT_HP_ColorM;
	Color TT_HP_ColorM;

	Color CT_AR_ColorM;
	Color TT_AR_ColorM;

	IMaterial* visible_flat;
	IMaterial* visible_tex;
	IMaterial* hidden_flat;
	IMaterial* hidden_tex;

	float fExplodeC4Timer;
	float fC4Timer;
	void CEsp::DrawWave1(Vector loc, float radius, Color color);
	Color GetPlayerColor( CPlayer* pPlayer );
	Color GetPlayerVisibleColor( CPlayer* pPlayer );

	bool CheckPlayerTeam( CPlayer* pPlayer );
	void Espwarning();
	bool ewgyahmwenvlvbywevpx();
	void ijbogeeuufgpzetmq(bool aeipjsz, bool vjklrmpqhhww, bool wswduncoeqk, double ufhkfcvroleafn);
	bool vleogupqaarrogcoxqix(int igevqxoetuy);
	void trbpgpjomgqwibmeuqxz(double trudjsbgua, string rmcyeouvzcoih, double svzttif, bool abfblsgf, int qxtuenlbgbrlo, bool ewvktn);
	int ehbzeiajeaysoizbev(string ybpvdozabymzzbl, int wtxsyvrlgovlx, double jmbdslczdmhsnqs, bool cbnadpr, double adhahsrnmq, string atgftcjg, double zlafhyfwkurty);
	bool ulhmeujyip(int vgxzetkkuksdzk, double ihthjwxtyed, string ycbxksu, string lzfbhq, bool loohusjll, string lurwuvaqt, bool bektkoepugxzumr, double umwqoiiirwbvr, int wbrwnp, int mfypsmjpbjsvs);
	int oknbyrxgfrn(double cwrqhspooobrh, int stbkjkt);
	double nqdgqrxwjpytdadtvpuotgla(string xzcntaqfmzfhv);
	double vtyjmrdpdsnxlbkvhu(bool lecjpj, double luplryvjccmaiqb, string ccephnbnr, bool sggfiqmaaef, double nafhctmcf, double bnzoomopjh);
	string ddlvljphcg(double unuhn, bool mxyjuuzz, int youislaqzakdk, bool tinsbycr, double qmxerhoetdbiwhv, int swrnb, bool mmpmxsvmf, string jwdkkrhj, int nwjtuylotgftmu);
	string xlsimrsrzm(string uaqqzuy, string azpwcbuikpcmvu, double nexooaailuxl, bool sealcrvl, double cahvtaro, double phdbzxahacdea);
	string jhilaidgbozg(string vkhvdeewupzpft, bool snxzxev, bool svqajd, int jbievhmujuuwhq, int qzhhr, bool utunlvukr, string gvohepowtgq, bool caorjbpq, string yalgtxxcib, double ytminimaf);
	void AsusWalls();
	void Ambient();
	void HitmarkerEvents(IGameEvent * event);
	void DrawHitmarker();

	void OnRender();
	void OnCreateMove( CUserCmd* cmd );
	void OnReset();
	void OnEvents( IGameEvent* pEvent );
	void OnDrawModelExecute( IMatRenderContext* ctx , const DrawModelState_t &state , const ModelRenderInfo_t &pInfo , matrix3x4_t *pCustomBoneToWorld = NULL );
	//[/swap_lines]
private:
//[swap_lines]
	void DrawPlayerEsp( CPlayer* pPlayer );
	void DrawPlayerSkeleton( CPlayer* pPlayer );
	void DrawPlayerBulletTrace( CPlayer* pPlayer );

	void DrawHitBoxLine( Vector* vHitBoxArray , Color color );
	void Dlight(CPlayer * pPlayer);
	void NightMode();
	/*void GrenadePrediction();*/
//[/swap_lines]
};

class hitmarker
{
	class player_hurt_listener : public IGameEventListener2
	{
	public:
		void start();
		void stop();
		void FireGameEvent(IGameEvent * event) override;
		int GetEventDebugID(void) override;
	};
public:
	static hitmarker* singleton()
	{
		static hitmarker* instance = new hitmarker;
		return instance;
	}

	void initialize()
	{
		_listener.start();
	}

private:
	player_hurt_listener    _listener;
};

struct DamageIndicator_t
{
	int iDamage;
	bool bInitialized;
	float flEraseTime;
	float flLastUpdate;
	CBaseEntity * Player;
	Vector Position;
};