#pragma once
class ParticleManager
{
public:
	static ParticleManager& GetInstance()
	{
		static ParticleManager instance;
		return instance;
	}

	ParticleManager(ParticleManager const&) = delete;
	void operator=(ParticleManager const&) = delete;

private:
	ParticleManager(){}
};

