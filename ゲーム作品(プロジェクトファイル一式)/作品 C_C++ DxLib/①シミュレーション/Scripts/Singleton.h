#pragma once

// �V���O���g���N���X
template <class T>
class Singleton
{
protected:
	// �R���X�g���N�^�E�f�X�g���N�^�̋֎~
	Singleton() {}
	virtual ~Singleton() {}
private:
	// �R�s�[�R���X�g���N�^�E����̋֎~
	Singleton(const Singleton& r) {}
	Singleton& operator=(const Singleton& r) {}

public:
    static T& GetInstance() 
    {
        static T Instance;
        return Instance;
    }
};