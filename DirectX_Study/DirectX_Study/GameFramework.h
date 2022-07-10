#pragma once
class CGameFramework
{
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	int m_nWndClientWidth;
	int m_nWndClientHeight;

	std::unique_ptr<IDXGIFactory4> m_pdxgiFactory;	// DXGI 팩토리 인터페이스에 대한 포인터이다.
	std::unique_ptr<IDXGISwapChain3> m_pdxgiSwapChain;	// 스왑 체인 인터페이스에 대한 포인터이다. 주로 디스플레이를 제어하기 위하여 필요하다.
	std::unique_ptr<ID3D12Device> m_pd3dDevice;	// Direct3D 디바이스 인터페이스에 대한 포인터이다. 주로 리소스를 생성하기 위하여 필요하다.

	bool m_bMsaa4xEnable = false;
	UINT m_nMsaa4xQualityLevels = 0;	// MSAA 다중 샘플링을 활성화하고 다중 샘플링 레벨을 설정한다.

	static const UINT m_nSwapChainBuffers = 2;	// 스왑 체인의 후면 버퍼의 개수이다.
	UINT m_nSwapChainBufferIndex;	// 현재 스왑체인의 후면 버퍼 인덱스이다.

	std::unique_ptr<std::vector<ID3D12Resource>> m_ppd3RenderTargetBuffers;		// 렌더 타겟 버퍼 포인터
	std::unique_ptr<ID3D12DescriptorHeap> m_pd3dRtvDescriptorHeap;	// 서술자 힙 인터페이스 포인터
	UINT m_nRtvDescriptorIncrementSize;		// 렌더 타겟 서술자 원소의 크기

	std::unique_ptr<ID3D12Resource> m_pd3dDepthStencilBuffer;		// 깊이-스텐실 버퍼
	std::unique_ptr<ID3D12DescriptorHeap> m_pd3dDsvDescriptorHeap;	// 서술자 힙 인터페이스 포인터
	UINT m_nDsvDescriptorIncrementSize;		// 깊이-스텐실 서술자 원소의 크기

	std::unique_ptr<ID3D12CommandQueue> m_pd3dCommandQueue;		// 명령 큐 포인터
	std::unique_ptr<ID3D12CommandAllocator> m_pd3dCommandAllocator;		// 명령 할당자 포인터
	std::unique_ptr<ID3D12GraphicsCommandList> m_pd3dCommandList;	// 명령 리스트 인터페이스 포인터

	std::unique_ptr<ID3D12PipelineState> m_pd3dPipelineState;	// 그래픽스 파이프라인 상태 객체에 대한 인터페이스 포인터이다.

	std::unique_ptr<ID3D12Fence> m_pd3dFence;	// 펜스 인터페이스 포인터
	UINT64 m_nFenceValue;	// 펜스의 값
	HANDLE m_hFenceEvent;	// 이벤트 핸들

	D3D12_VIEWPORT m_d3dviewport;	// 뷰포트
	D3D12_RECT m_d3dScissorRect;	// 씨저 사각형
public:
	CGameFramework();
	~CGameFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);	// 프레임워크를 초기화하는 함수
	void OnDestory();

	void CreateSwapChain();		// 스왑 체인 생성 함수
	void CreateRtvAndDsvDescriptorHeaps();		// 디바이스 생성 함수
	void CreateDirect3DDevice();	// 서술자 힙 생성 함수
	void CreateCommandQueueAndList();		// 명령 큐/할당자/리스트 생성 함수

	void CreateRenderTargetViews();		// 렌더 타겟 뷰를 생성하는 함수이다.
	void CreateDepthStencilView();		// 깊이-스텐실 뷰를 생성하는 함수이다.

	void BuildObjects();	// 렌더링할 메쉬와 게임 객체를 생성하는 함수
	void ReleaseObjects();	// 렌더링할 메쉬와 게임 객체를 소멸하는 함수
 
	// 프레임워크의 핵심(사용자 입력, 애니메이션, 렌더링)을 구성하는 함수이다.
	void ProcessInput();	
	void AnimateObjects();
	void FrameAdvance();

	void WaitForGpuComplete();		// CPU와 GPU를 동기화하는 함수

	//윈도우의 메시지(키보드, 마우스 입력)를 처리하는 함수이다.
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
};

