#pragma once
class CDataMgr
{
private:
	CDataMgr();
	~CDataMgr();

public:
	void	Initialize();
	void	Late_Update();
	void	Release();

public:
	const int& Get_Coin() const { return coin; }
	const int& Get_Life() const { return life; }
	const int& Get_Score() const { return score; }

public:
	void		Set_Coin(int _coin) { coin = _coin; }
	void		Set_Score(int _score) { score = _score; }
	void		Set_Life(int _life) { life = _life; }

public:
	void		Add_Coin(int _i) { coin += _i;}
	void		Add_Life(int _i) { life += _i; }
	void		Add_Score(int _i) { score += _i; }

private:
	int		init_Life; 
	int		life;
	int		coin;
	int		score;

private:
	static CDataMgr* pInstance;

public:
	static CDataMgr* Get_Instance()
	{
		if (!pInstance)
		{
			pInstance = new CDataMgr;
		}

		return pInstance;
	}

	static void Destroy_Instance()
	{
		if (pInstance)
		{
			delete pInstance;
			pInstance = nullptr;
		}
	}
};

