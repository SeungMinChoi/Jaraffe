#pragma once

#define  ENGINE_NAME			L"Jaraffe Game Engine"
#define  START_CLIENT_WIDTH		1000
#define  START_CLIENT_HEIGHT	800

#define  MAIN_LIGHT_COUNT		3	// -> 무조건 1개 이상이여야한다 ( 이걸 바꾸면 셰이더쪽도 바꿔줘야함 )


// SmartPointer
#define JFPTR	std::shared_ptr
#define NEW		std::make_shared