#ifndef ROTMG_PACKETIDS
#define ROTMG_PACKETIDS

namespace rotmg {
	namespace PacketID {
		enum PacketID {
			FAILURE = 0,
			CREATE_SUCCESS = 59,
			CREATE = 49,
			PLAYERSHOOT = 20,
			MOVE = 61,
			PLAYERTEXT = 39,
			TEXT = 7,
			SHOOT = 21,
			MULTI_SHOOT = 31,
			DAMAGE = 38,
			UPDATE = 5,
			NOTIFICATION = 63,
			NEW_TICK = 57,
			INVSWAP = 65,
			USEITEM = 58,
			SHOW_EFFECT = 77,
			HELLO = 17,
			GOTO = 50,
			INVDROP = 11,
			INVRESULT = 75,
			RECONNECT = 4,
			PING = 27,
			MAPINFO = 37,
			LOAD = 34,
			PIC = 3,
			SET_CONDITION = 28,
			TELEPORT = 23,
			USE_PORTAL = 45,
			DEATH = 47,
			BUY = 68,
			BUY_RESULT = 10,
			AOE = 62,
			GROUND_DAMAGE = 19,
			PLAYERHIT = 18,
			ENEMYHIT = 24,
			AOE_ACKNOWLEDGE = 26,
			SHOOT_ACKNOWLEDEGE = 64,
			OTHERHIT = 6,
			SQUAREHIT = 16,
			GOTO_ACKNOWLEDGE = 51,
			EDIT_ACCOUNT_LIST = 55,
			ACOUNT_LIST = 66,
			QUEST_OBJECT_ID = 74,
			CHOOSE_NAME = 40,
			NAME_RESULT = 67,
			CREATE_GUILD = 76,
			CREATE_GUILD_RESULT = 69,
			GUILD_REMOVE = 8,
			GUILD_INVITE = 22,
			ALLY_SHOOT = 53,
			REQUEST_TRADE = 48,
			TRADE_REQUESTED = 36,
			TRADE_START = 9,
			CHANGE_TRADE = 12,
			TRADE_CHANGED = 44,
			ACCEPT_TRADE = 15,
			CANCEL_TRADE = 25,
			TRADE_DONE = 42,
			CLIENT_STAT = 46,
			CHECK_CREDITS = 30,
			ESCAPE = 33,
			FILE = 56,
			INVITE_TO_GUILD = 35,
			JOIN_GUILD = 52,
			CHANGE_GUILD_RANK = 60,
			PLAY_SOUND = 13
		};
	}
}

#endif