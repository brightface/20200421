#pragma once
#include "stdafx.h"
//singTone Pattern
class Settings final
{
public:
	static Settings& Get()
	{//static �Լ�: �������� ��ü���� �����Ҽ� �ִ� �Լ��̴�.
		static Settings instance;
		return instance; //static ���������� ó���� �ʱ�ȭ �ǰ� �ʱ�ȭ ������ 0���� �ʱ�ȭ�ȴ�.
	}
	//�׷��� �߰������� ���� �Լ����� get�� ���ؼ� �ν��Ͻ� ������ �����Ҽ� �ִ�.
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
	//settings���� ������ ��ڴ�. �������� ������ �׷�������
	//�������� �����Ҽ��ִ� �������� ����Ŵ�.
	//�̱��� �츮��� �̱��ϳ��� ��ü�� ���ϳ��� ����
	//�����ڸ� ����ڴ�
	//��� c++���� default �߰��� ����̴�.
	//Settings() {}; �̰Ͱ� ����.

};
