#pragma once
#include<vector>
#include<string>
#include<map>

using namespace std;

class GameObjectBlueprint {

private:
	string m_Name = "";
	vector<string> m_ComponentList;
	string m_BitmapName = "";
	int m_Health;
	float m_Width;
	float m_Height;
	float m_LocationX;
	float m_LocationY;
	float m_Speed;
	bool m_EncompassingRectCollider = false;
	string m_EncompassingRectColliderLabel = "";

public:
	float getWidth();
	void setWidth(float width);
	float getHeight();
	void setHeight(float height);
	float getLocationX();
	void setLocationX(float locationX);
	float getLocationY();
	void setLocationY(float locationY);
	void setName(string name);
	string getName();
	void setHealth(int health);
	int getHealth();
	vector<string>& getComponentList();
	void addToComponentList(string newComponent);
	string getBitmapName();
	void setBitmapName(string bitmapName);
	string getEncompassingRectColliderLabel();
	bool getEncompassingRectCollider();
	void setEncompassingRectCollider(string label);
};

