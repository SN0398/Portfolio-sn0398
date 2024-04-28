#pragma once

// シングルトンクラス
template <class T>
class Singleton
{
protected:
	// コンストラクタ・デストラクタの禁止
	Singleton() {}
	virtual ~Singleton() {}
private:
	// コピーコンストラクタ・代入の禁止
	Singleton(const Singleton& r) {}
	Singleton& operator=(const Singleton& r) {}

public:
    static T& GetInstance() 
    {
        static T Instance;
        return Instance;
    }
};