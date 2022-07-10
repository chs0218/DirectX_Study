#pragma once
class CGameFramework
{
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	int m_nWndClientWidth;
	int m_nWndClientHeight;

	std::unique_ptr<IDXGIFactory4> m_pdxgiFactory;	// DXGI ���丮 �������̽��� ���� �������̴�.
	std::unique_ptr<IDXGISwapChain3> m_pdxgiSwapChain;	// ���� ü�� �������̽��� ���� �������̴�. �ַ� ���÷��̸� �����ϱ� ���Ͽ� �ʿ��ϴ�.
	std::unique_ptr<ID3D12Device> m_pd3dDevice;	// Direct3D ����̽� �������̽��� ���� �������̴�. �ַ� ���ҽ��� �����ϱ� ���Ͽ� �ʿ��ϴ�.

	bool m_bMsaa4xEnable = false;
	UINT m_nMsaa4xQualityLevels = 0;	// MSAA ���� ���ø��� Ȱ��ȭ�ϰ� ���� ���ø� ������ �����Ѵ�.

	static const UINT m_nSwapChainBuffers = 2;	// ���� ü���� �ĸ� ������ �����̴�.
	UINT m_nSwapChainBufferIndex;	// ���� ����ü���� �ĸ� ���� �ε����̴�.

	std::unique_ptr<std::vector<ID3D12Resource>> m_ppd3RenderTargetBuffers;		// ���� Ÿ�� ���� ������
	std::unique_ptr<ID3D12DescriptorHeap> m_pd3dRtvDescriptorHeap;	// ������ �� �������̽� ������
	UINT m_nRtvDescriptorIncrementSize;		// ���� Ÿ�� ������ ������ ũ��

	std::unique_ptr<ID3D12Resource> m_pd3dDepthStencilBuffer;		// ����-���ٽ� ����
	std::unique_ptr<ID3D12DescriptorHeap> m_pd3dDsvDescriptorHeap;	// ������ �� �������̽� ������
	UINT m_nDsvDescriptorIncrementSize;		// ����-���ٽ� ������ ������ ũ��

	std::unique_ptr<ID3D12CommandQueue> m_pd3dCommandQueue;		// ��� ť ������
	std::unique_ptr<ID3D12CommandAllocator> m_pd3dCommandAllocator;		// ��� �Ҵ��� ������
	std::unique_ptr<ID3D12GraphicsCommandList> m_pd3dCommandList;	// ��� ����Ʈ �������̽� ������

	std::unique_ptr<ID3D12PipelineState> m_pd3dPipelineState;	// �׷��Ƚ� ���������� ���� ��ü�� ���� �������̽� �������̴�.

	std::unique_ptr<ID3D12Fence> m_pd3dFence;	// �潺 �������̽� ������
	UINT64 m_nFenceValue;	// �潺�� ��
	HANDLE m_hFenceEvent;	// �̺�Ʈ �ڵ�

	D3D12_VIEWPORT m_d3dviewport;	// ����Ʈ
	D3D12_RECT m_d3dScissorRect;	// ���� �簢��
public:
	CGameFramework();
	~CGameFramework();

	bool OnCreate(HINSTANCE hInstance, HWND hMainWnd);	// �����ӿ�ũ�� �ʱ�ȭ�ϴ� �Լ�
	void OnDestory();

	void CreateSwapChain();		// ���� ü�� ���� �Լ�
	void CreateRtvAndDsvDescriptorHeaps();		// ����̽� ���� �Լ�
	void CreateDirect3DDevice();	// ������ �� ���� �Լ�
	void CreateCommandQueueAndList();		// ��� ť/�Ҵ���/����Ʈ ���� �Լ�

	void CreateRenderTargetViews();		// ���� Ÿ�� �並 �����ϴ� �Լ��̴�.
	void CreateDepthStencilView();		// ����-���ٽ� �並 �����ϴ� �Լ��̴�.

	void BuildObjects();	// �������� �޽��� ���� ��ü�� �����ϴ� �Լ�
	void ReleaseObjects();	// �������� �޽��� ���� ��ü�� �Ҹ��ϴ� �Լ�
 
	// �����ӿ�ũ�� �ٽ�(����� �Է�, �ִϸ��̼�, ������)�� �����ϴ� �Լ��̴�.
	void ProcessInput();	
	void AnimateObjects();
	void FrameAdvance();

	void WaitForGpuComplete();		// CPU�� GPU�� ����ȭ�ϴ� �Լ�

	//�������� �޽���(Ű����, ���콺 �Է�)�� ó���ϴ� �Լ��̴�.
	void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
};

