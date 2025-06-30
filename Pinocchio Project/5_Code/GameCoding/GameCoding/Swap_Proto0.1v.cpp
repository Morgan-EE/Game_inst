//// Swap_Prac2.cpp : 애플리케이션에 대한 진입점을 정의합니다.
////

#include "pch.h"
#include "Swap_Proto0.1v.h"
//
//#define MAX_LOADSTRING 100
//
//// 전역 변수:
//HINSTANCE hInst;                                // 현재 인스턴스입니다.
//WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
//WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
//
//// 이 코드 모듈에 포함된 함수의 선언을 전달합니다: 함수 전방 선언
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//
//int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
//                     _In_opt_ HINSTANCE hPrevInstance,
//                     _In_ LPWSTR    lpCmdLine,
//                     _In_ int       nCmdShow)
//{
//    UNREFERENCED_PARAMETER(hPrevInstance);
//    UNREFERENCED_PARAMETER(lpCmdLine);
//
//    // TODO: 여기에 코드를 입력합니다.
//
//    // 전역 문자열을 초기화합니다.
//    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
//    LoadStringW(hInstance, IDC_SWAPPRAC2, szWindowClass, MAX_LOADSTRING);
//    MyRegisterClass(hInstance);
//
//    // 애플리케이션 초기화를 수행합니다:
//    if (!InitInstance (hInstance, nCmdShow))
//    {
//        return FALSE;
//    }
//
//    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SWAPPRAC2));
//
//    MSG msg;
//
//    // 기본 메시지 루프입니다:
//    while (GetMessage(&msg, nullptr, 0, 0))
//    {
//        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
//        {
//            TranslateMessage(&msg);
//            DispatchMessage(&msg);
//        }
//    }
//
//    return (int) msg.wParam;
//}
//
//
//
////
////  함수: MyRegisterClass()
////
////  용도: 창 클래스를 등록합니다.
////
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//    WNDCLASSEXW wcex;
//
//    wcex.cbSize = sizeof(WNDCLASSEX);
//
//    wcex.style          = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc    = WndProc;
//    wcex.cbClsExtra     = 0;
//    wcex.cbWndExtra     = 0;
//    wcex.hInstance      = hInstance;
//    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SWAPPRAC2));
//    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
//    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SWAPPRAC2);
//    wcex.lpszClassName  = szWindowClass;
//    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//    return RegisterClassExW(&wcex);
//}
//
////
////   함수: InitInstance(HINSTANCE, int)
////
////   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
////
////   주석:
////
////        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
////        주 프로그램 창을 만든 다음 표시합니다.
////
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
//
//   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//   if (!hWnd)
//   {
//      return FALSE;
//   }
//
//   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);
//
//   return TRUE;
//}
//
//
///// <summary>
///// 플레이어가 1,5 스테이지에 위치하는지 확인하고, 있으면 true (stage[0,4]만 빼면됨)
///// 엣지에 없으면 false를 출력합니다. (stage[0,4]+stage[플레이어]를 빼야함)
///// </summary>
///// <param name="stage"></param>
///// <returns></returns>
//
//// 210 <= stage1.x < 510, 510 <= stage2.x < 810, 810 <= stage3.x < 1110, 1110 <= stage4.x < 1710, 210 <= stage5.x < 1710, 
//// 플레이어가 [1,5]위치, case1
//// 플레이어가 [2]위치,   case2
//// 플레이어가 [3]위치,   case3
//// 플레이어가 [4]위치,   case4
//int CheckPlayerPos()
//{
//    if (player.x >= 210 && player.x < 510)
//        return 1;
//    else if (player.x >= 510 && player.x < 810)
//        return 2;
//    else if (player.x >= 810 && player.x < 1110)
//        return 3;
//    else if (player.x >= 1110 && player.x < 1410)
//        return 4;
//    else if (player.x >= 1410 && player.x < 1710)
//        return 1;
//    else
//        return -1;
//}
//
///// <summary> 일단 스테이지는 직관성을 위해 [1,2,3,4,5]로 가정합니다.
///// 
///// 플레이어가 [1,5]위치, case1 -> stage[2,3,4] movable 판정
///// 플레이어가 [2]위치,   case2 -> stage[3,4]   movable 판정
///// 플레이어가 [3]위치,   case3 -> stage[2,4]   movable 판정
///// 플레이어가 [4]위치,   case4 -> stage[2,3]   movable 판정
///// 
///// </summary>
//void CheckStageMovable()
//{
//    int stage[5] = { 1,2,3,4,5 };
//
//    switch (CheckPlayerPos())
//    {
//    case 1:
//        // stage[2,3,4] move
//
//        break;
//    case2:
//        // stage[3,4]
//        break;
//    case3:
//        // stage[2,4]
//        break;
//    case4:
//        // stage[2,3]
//        break;
//    default:
//        //?
//    }
//
//    return 0;
//}
//
///// <summary>
///// 스테이지의 CheckStageMovable이 true 값인 배열을 뽑아 재배열화하여 저장하는 함수
///// </summary>
////void SetMovableStages()
////{
////    
////}
//
//int GetSelectedStageNum(int stage[5])
//{
//    // 여기에서 플레이어의 존재 여부를 확인하고 해당 스테이지의 배열 숫자를 반환하는 로직을 구현합니다.
//    // 예를 들어, collision 속성을 체크하거나 다른 방식으로 플레이어의 존재 여부를 판단할 수 있습니다.
//
//    // 플레이어의 존재 여부를 확인하는 예시 코드
//    for (int i = 0; i < 5; i++)
//    {
//        if (stage[i] == 5) // 플레이어 숫자에 해당하는 값으로 변경해야 합니다.
//        {
//            return i;
//        }
//    }
//
//    // 플레이어가 없는 경우 -1을 반환
//    return -1;
//}
//
//
//
//
//
//
//
//
///// <summary>
///// 배열 value를 바꾸는 swap 함수입니다.
///// </summary>
///// 
//void SwaptoRight(int stage[5])
////arr[0] (arr[1])>arr[2]  arr[3] arr[4]
////arr[0]  arr[2] (arr[1]) arr[3] arr[4]
//{
//    int select_stage_num = 1; // 선택한 스테이지 숫자를 감지하여 입력받음
//
//    int temp;                             //int mov_base = 1; //일단 기본값을 1로 설정함, 추후 position 측정하여 변경할것.
//    int mov_right = select_stage_num - 1; //오른쪽요소 왼쪽으로 이동
//
//    temp = stage[select_stage_num];
//    stage[select_stage_num] = stage[mov_right];
//    stage[mov_right] = temp;
//}
//void SwaptoLeft(int stage[5])
////arr[0]  arr[1]<(arr[2]) arr[3] arr[4]
////arr[0] (arr[2]) arr[1] arr[3] arr[4]
//{
//    int temp;
//    int mov_base=1; //일단 기본값을 1로 설정함, 추후 position 측정하여 변경할것.
//    int mov_left = mov_base + 1; //오른쪽요소 왼쪽으로 이동
//    temp = stage[mov_base];
//    stage[mov_base] = stage[mov_left];
//    stage[mov_left] = temp;
//}
//
//
//
////  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  용도: 주 창의 메시지를 처리합니다.
////  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
////  WM_PAINT    - 주 창을 그립니다.
////  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    static int arr[5] = {1,2,3,4,5};
//
//    switch (message)
//    {
//    case WM_KEYDOWN:
//    {
//        int key = wParam; // 입력된 키를 가져옵니다
//        void Swap(int arr[5]);
//
//        switch (key)
//        {
//
//        case 'A': // 왼쪽 키
//            SwaptoLeft(arr);
//            InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신을 요청합니다
//            break;
//
//        case 'D': // 오른쪽 키
//            SwaptoRight(arr);
//            InvalidateRect(hWnd, NULL, TRUE); // 화면 갱신을 요청합니다
//            break;
//        }
//
//    }
//    case WM_COMMAND:
//        {
//            int wmId = LOWORD(wParam);
//            // 메뉴 선택을 구문 분석합니다:
//            switch (wmId)
//            {
//            case IDM_ABOUT:
//                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//                break;
//            case IDM_EXIT:
//                DestroyWindow(hWnd);
//                break;
//            default:
//                return DefWindowProc(hWnd, message, wParam, lParam);
//            }
//        }
//        break;
//
//    case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hWnd, &ps);
//            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
//
//            int x = 500; // X 좌표 시작점
//
//            for (int i = 0; i < 5; i++)
//            {
//                
//                // 각 요소를 문자열로 변환하여 출력합니다
//                WCHAR str[10];
//                swprintf_s(str, L"%d", arr[i]);
//
//                TextOut(hdc, x, 200, str, wcslen(str));
//
//                // 다음 요소를 출력하기 위해 X 좌표를 증가시킵니다
//                x += 20; //요소 사이의 간격 조정, 필요에 따라 수정 가능
//            }
//
//            EndPaint(hWnd, &ps);
//        }
//        break;
//
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
//
//// 정보 대화 상자의 메시지 처리기입니다.
//INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    UNREFERENCED_PARAMETER(lParam);
//    switch (message)
//    {
//    case WM_INITDIALOG:
//        return (INT_PTR)TRUE;
//
//    case WM_COMMAND:
//        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//        {
//            EndDialog(hDlg, LOWORD(wParam));
//            return (INT_PTR)TRUE;
//        }
//        break;
//    }
//    return (INT_PTR)FALSE;
//}
