//#include "SceneManager.h"
//
//using namespace std;
//
//SceneManager::SceneManager()
//{
//    return;
//}
//
//SceneManager::~SceneManager()
//{
//    PopAllScene();
//    return;
//}
//
//void SceneManager::PopScene()
//{
//    s_stack.pop();
//    return;
//}
//
////bool SceneManager::PushScene(Define::SceneType Stype)
////{
////    switch (Stype)
////    {
////    case Define::SceneType::Title:
////    {
////        s_stack.push(make_unique<Title>());
////        break;
////    }
////    case Define::SceneType::Game:
////    {
////        s_stack.push(make_unique<Game>());
////        break;
////    }
////    default:
////    {
////        return false;
////    }
////    }
////    return true;
////}
//
//void SceneManager::PopAllScene()
//{
//    // �X�^�b�N��S�폜
//    while (!s_stack.empty())
//    {
//        PopScene();
//    }
//}
//
//template <class T>
//void SceneManager::ChangeScene(Define::CS_CallType CStype)
//{
//    switch (CStype)
//    {
//    case Define::CS_CallType::PopAll:   // �X�^�b�N�������ׂď����Ă���擪�ɒǉ�
//    {
//        PopAllScene();
//        s_stack.push(make_unique<T>());
//        return;
//    }
//    case Define::CS_CallType::PopTop:   // �擪�̃X�^�b�N������
//    {
//        PopScene();
//        s_stack.push(make_unique<T>());
//        return;
//    }
//    case Define::CS_CallType::Push:     // �擪�ɒǉ�
//    {
//        s_stack.push(make_unique<T>());
//        return;
//    }
//    default:
//    {
//        break;
//    }
//    }
//    return false;
//}
//
//void SceneManager::BackScene()
//{
//    PopScene();
//    return;
//}