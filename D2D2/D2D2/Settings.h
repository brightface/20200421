#pragma once
#include "stdafx.h"
//singTone Pattern
class Settings final
{
public:
	static Settings& Get()
	{//static 함수: 전역에서 객체없이 접근할수 있는 함수이다.
		static Settings instance;
		return instance; //static 정적변수라 처음만 초기화 되고 초기화 없을시 0으로 초기화된다.
	}
	//그러나 추가적으로 만들 함수들은 get을 통해서 인스턴스 만든후 접근할수 있다.
	auto GetWindowHandle()-> HWND { return handle; }
	void SetWindowHandle(HWND handle) { this->handle = handle; }

	auto GetWidth() const -> const float& { return width; }
	void SetWidth(const float& width) { this->width - width; }

	auto GetHeight() const -> const float& { return height; }
	void SetHeight(const float& height) { this->height - height; }
	

private:
	Settings() = default;
	~Settings() = default;
private:
	HWND handle = nullptr;
	float width = 0.0f;
	float height = 0.0f;
	//settings에다 정보를 담겠다. 꺼내쓰기 쉽도록 그래서만듬
	//누구든지 접근할수있는 전역으로 만들거다.
	//싱글톤 우리모두 싱글하나만 객체가 단하나만 존재
	//생성자를 숨기겠다
	//모던 c++에서 default 추가된 기능이다.
	//Settings() {}; 이것과 같다.

};
