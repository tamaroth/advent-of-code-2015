/************************************************************************/
/* Advent of Code:
/* Day 22: Wizard Simulator 20XX
/************************************************************************/

#include <algorithm>
#include <iostream>
#include <chrono>
#include <string>
#include <array>

class CGame
{
public:
	enum class RESULT {
		PLOST = 1,
		PWON = 2,
		SCAST = 4,
	};

	enum class SPELL {
		RECHARGE = 0,
		POISON = 1,
		SHIELD = 2,
		MMISSLE = 3,
		DRAIN = 4,
	};
	
	typedef struct _Spell
	{
		SPELL	name;
		int		mana_cost;
		int		damage;
		int		armour;
		int		health;
		int		mana;
		int		duration;
	} Spell;

	typedef struct _State
	{
		int		hp;
		int		mana;
		int		spentMana;
		int		bossHP;
		std::array<Spell, 3> effects;
	} State;

public:
	CGame() {};
	CGame(int hp, int damage, int hard=0) : 
		  m_bossDamage(damage)
		, m_hard(hard)
		, m_armour(0)
		, m_lowestMana(5000)
	{
		m_gameState.hp = 50;
		m_gameState.bossHP = hp;
		m_gameState.mana = 500;
		m_gameState.spentMana = 0;
		m_gameState.effects = { {
			{ SPELL::RECHARGE, 229, 0, 0, 0, 101, 0 },
			{ SPELL::POISON,   173, 3, 0, 0, 0, 0 },
			{ SPELL::SHIELD,   113, 0, 7, 0, 0, 0 }
		} };
	};
	~CGame() {};
	int startGame();
	int getSpentMana() { return m_lowestMana; };

private:
	RESULT effects();
	RESULT castSpell(const Spell& spell);
	RESULT turn(const Spell& spell);
	bool success(RESULT res) { return (res != RESULT::PLOST); };
	bool won(RESULT res) { return (res == RESULT::PWON); };
	bool lost(RESULT res) { return (res == RESULT::PLOST); };
private:
	std::array<Spell, 5> m_spells = { {
		{SPELL::MMISSLE,   53, 4, 0, 0, 0, 0},
		{SPELL::DRAIN,     73, 2, 0, 2, 0, 0},
		{SPELL::SHIELD,   113, 0, 7, 0, 0, 6},
		{SPELL::POISON,   173, 3, 0, 0, 0, 6},
		{SPELL::RECHARGE, 229, 0, 0, 0, 101, 5}
	} };
	State	m_gameState;
	int		m_bossDamage;
	int		m_armour;
	int		m_hard;
	int		m_lowestMana;
};

CGame::RESULT CGame::effects() 
{
	m_armour = 0;
	for (auto& ev : m_gameState.effects)
	{
		if (ev.duration)
		{
			ev.duration--;
			m_armour = ev.armour;
			m_gameState.bossHP -= ev.damage;
			m_gameState.mana += ev.mana;
		}
		
		if (m_gameState.bossHP <= 0)
			return RESULT::PWON;
	}

	return RESULT::SCAST;
}

CGame::RESULT CGame::castSpell(const Spell& spell)
{
	if (spell.mana_cost <= m_gameState.mana)
	{
		m_gameState.mana -= spell.mana_cost;
		m_gameState.spentMana += spell.mana_cost;
		if (spell.duration)
		{
			if (spell.name != SPELL::MMISSLE && spell.name != SPELL::DRAIN && m_gameState.effects[std::underlying_type<RESULT>::type(spell.name)].duration == 0)
			{
				m_gameState.effects[std::underlying_type<RESULT>::type(spell.name)] = spell;
			}
		}
		else
		{
			m_gameState.bossHP -= spell.damage;
			m_gameState.hp += spell.health;
		}
	}
	else
	{
		return RESULT::PLOST;
	}
	if (m_gameState.bossHP <= 0)
	{
		return RESULT::PWON;
	}
	return RESULT::SCAST;
}

CGame::RESULT CGame::turn(const Spell& spell)
{
	RESULT lastRes = RESULT::SCAST;

	m_gameState.hp -= m_hard;
	if (m_gameState.hp <= 0)
		return RESULT::PLOST;

	if (won(effects()))
	{
		m_lowestMana = std::min(m_lowestMana, m_gameState.spentMana);
		return RESULT::PWON;
	}

	if (won(lastRes = castSpell(spell)))
	{
		m_lowestMana = std::min(m_lowestMana, m_gameState.spentMana);
		return RESULT::PWON;
	}

	if (lost(lastRes))
	{
		return RESULT::PLOST;
	}

	if (won(effects()))
	{
		m_lowestMana = std::min(m_lowestMana, m_gameState.spentMana);
		return RESULT::PWON;
	}

	m_gameState.hp = m_gameState.hp - std::max((m_bossDamage - m_armour), 1);
	if (m_gameState.hp <= 0 || m_gameState.mana <= 0 || lost(lastRes))
	{
		return RESULT::PLOST;
	}

	for (const auto& sp : m_spells)
	{
		if (!sp.duration || sp.name != spell.name)
		{
			State state = m_gameState;
			lastRes = turn(sp);
			m_gameState = state;
		}
	}
	return lastRes;
}

int CGame::startGame()
{
	for (auto& spell : m_spells)
	{
		State state = m_gameState;
		turn(spell);
		m_gameState = state;
	}
	return 0;
}

int partOne()
{
	CGame game(51, 9);
	game.startGame();
	return game.getSpentMana();
}

int partTwo()
{
	CGame game(51, 9, 1);
	game.startGame();
	return game.getSpentMana();
}

int main()
{
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::cout << "Part One: " << partOne() << std::endl;
	std::cout << "Part Two: " << partTwo() << std::endl;
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - t1);
	std::cout << "Time: " << time_span.count() << "s.";
	return 0;
}