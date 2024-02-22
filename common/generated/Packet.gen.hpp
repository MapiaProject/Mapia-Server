#pragma once

template<class T> inline T& unmove(T&& t) { return static_cast<T&>(t); }

namespace gen {
    enum PacketId : uint16 {
        NONE = 0,
		LOGIN_REQ = 1,
		ENTER_GAME_REQ = 2,
		ENTER_ROOM_REQ = 3,
		LOGIN_RES = 4,
		ENTER_GAME_RES = 5,
		ENTER_ROOM_RES = 6    
	};

}