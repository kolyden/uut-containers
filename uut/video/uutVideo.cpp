#include "uutVideo.h"
#include "uutWindow.h"
#include "uutTexture.h"
#include "uutShader.h"
#include "uutRenderBuffer.h"

namespace uut
{
	Video::Video()
		: _swapChain(0)
		, _device(0)
		, _context(0)
		, _renderTarget(0)
	{
	}

	bool Video::SetMode(int width, int height, bool fullscreen)
	{
		if (_window == nullptr)
		{
			_window = new Window();
			_window->Create(width, height);
		}

		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
		scd.BufferCount = 1;                                    // one back buffer
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
		scd.BufferDesc.Width = width;
		scd.BufferDesc.Height = height;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
		scd.OutputWindow = _window->GetHWND();
		scd.SampleDesc.Count = 4;
		scd.Windowed = fullscreen ? FALSE : TRUE;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		// create a device, device context and swap chain using the information in the scd struct
		D3D11CreateDeviceAndSwapChain(NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			D3D11_CREATE_DEVICE_DEBUG,
			NULL,
			NULL,
			D3D11_SDK_VERSION,
			&scd,
			&_swapChain,
			&_device,
			NULL,
			&_context);

		_backBuffer = new Texture(this);
		_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&_backBuffer->_data);

		_device->CreateRenderTargetView(_backBuffer->_data, NULL, &_renderTarget);
		_context->OMSetRenderTargets(1, &_renderTarget, NULL);

		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = 1.0f*width;
		viewport.Height = 1.0f*height;

		_context->RSSetViewports(1, &viewport);

		if (fullscreen)
			_swapChain->SetFullscreenState(TRUE, NULL);

		return true;
	}

	Video::~Video()
	{
		if (_swapChain)
		{
			_swapChain->SetFullscreenState(FALSE, NULL);
			_swapChain->Release();
		}

		if (_renderTarget)
			_renderTarget->Release();
		if (_device)
			_device->Release();
		if (_context)
			_context->Release();
	}

	bool Video::MessagePool()
	{
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// translate keystroke messages into the right format
			TranslateMessage(&msg);

			// send the message to the WindowProc function
			DispatchMessage(&msg);

			// check to see if it's time to quit
			if (msg.message == WM_QUIT)
				return false;
		}

		return true;
	}

	void Video::ClearTarget(const Color& color)
	{
		_context->ClearRenderTargetView(_renderTarget, color.m);
	}

	void Video::Present()
	{
		auto ret = _swapChain->Present(0, 0);
	}

	static DXGI_FORMAT SelectFormat(VertexType type, uint8_t count)
	{
		switch (type)
		{
		case uut::VertexType::SByte:
			break;

		case uut::VertexType::UByte:
			break;

		case uut::VertexType::SShort:
			break;

		case uut::VertexType::UShort:
			break;

		case uut::VertexType::Float:
			switch (count)
			{
			case 3:return DXGI_FORMAT_R32G32B32_FLOAT;
			case 4:return DXGI_FORMAT_R32G32B32A32_FLOAT;
			}
			break;
		}

		return DXGI_FORMAT_UNKNOWN;
	}

	SharedPtr<Shader> Video::CreateShaderFromMemory(const VertexDeclare* decl, uint8_t count, const char* code, int size /* = -1 */)
	{
		if (code == nullptr)
			return SharedPtr<Shader>::EMPTY;

		if (size < 0)
			size = strlen(code);
		if (code == 0)
			return SharedPtr<Shader>::EMPTY;

		SharedPtr<Shader> shader(new Shader(this));
		auto ret = D3DCompile(code, size, "memory", 0, 0, "VShader", "vs_4_0", 0, 0, &shader->_vsBlob, 0);
		if (ParseReturn(ret))
			return SharedPtr<Shader>::EMPTY;

		ret = _device->CreateVertexShader(shader->_vsBlob->GetBufferPointer(), shader->_vsBlob->GetBufferSize(), NULL, &shader->_vs);
		if (ParseReturn(ret))
			return SharedPtr<Shader>::EMPTY;

		ret = D3DCompile(code, size, "memory", 0, 0, "PShader", "ps_4_0", 0, 0, &shader->_psBlob, 0);
		if (ParseReturn(ret))
			return SharedPtr<Shader>::EMPTY;

		ret = _device->CreatePixelShader(shader->_psBlob->GetBufferPointer(), shader->_psBlob->GetBufferSize(), NULL, &shader->_ps);
		if (ParseReturn(ret))
			return SharedPtr<Shader>::EMPTY;

		//////////////////////////////////////////////////////////////////////////
		static const char* semanticName[3] = { "POSITION", "TEXCOORDS", "COLOR" };

		shader->_declare = List<VertexDeclare>(decl, count);

		List<D3D11_INPUT_ELEMENT_DESC> desc;
		desc.SetSize(count);

		for (int i = 0; i < count; i++)
		{
			desc[i].SemanticName = semanticName[(int)decl[i]._usage];
			desc[i].SemanticIndex = 0;
			desc[i].Format = SelectFormat(decl[i]._type, decl[i]._count);
			desc[i].InputSlot = 0;
			desc[i].AlignedByteOffset = decl[i]._offset;
			desc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			desc[i].InstanceDataStepRate = 0;
		}

		ret = _device->CreateInputLayout(desc.GetData(), count,
			shader->_vsBlob->GetBufferPointer(),
			shader->_vsBlob->GetBufferSize(), &shader->_layout);
		if (ret != S_OK)
			return SharedPtr<Shader>::EMPTY;

		return shader;
	}

	SharedPtr<RenderBuffer> Video::CreateBuffer(unsigned int size)
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = size;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		SharedPtr<RenderBuffer> buffer(new RenderBuffer(this));
		auto ret = _device->CreateBuffer(&bd, NULL, &buffer->_data);
		if (ParseReturn(ret))
			return SharedPtr<RenderBuffer>::EMPTY;

		return buffer;
	}

	bool Video::SetShader(Shader* shader)
	{
		if (shader == nullptr)
			return false;

		_context->VSSetShader(shader ? shader->_vs : nullptr, 0, 0);
		_context->PSSetShader(shader ? shader->_ps : nullptr, 0, 0);
		_context->IASetInputLayout(shader->_layout);

		return true;
	}

	bool Video::SetBuffer(RenderBuffer* buffer, unsigned int stride, unsigned int offset)
	{
		if (buffer == nullptr)
			return false;

		UINT _stride = stride;
		UINT _offset = offset;
		_context->IASetVertexBuffers(0, 1, &buffer->_data, &_stride, &_offset);
		return true;
	}

	bool Video::SetTopology(VertexTopology topology)
	{
		switch (topology)
		{
		case VertexTopology::PointList:
			_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
			break;

		case VertexTopology::LineList:
			_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
			break;

		case VertexTopology::LineStrip:
			_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
			break;

		case VertexTopology::TriangleList:
			_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			break;

		case VertexTopology::TriangleStrip:
			_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			break;
		}

		return true;
	}

	bool Video::Draw(unsigned int count, unsigned int start)
	{
		_context->Draw(count, start);
		return true;
	}

	Window* Video::GetWindow() const
	{
		return _window;
	}

	//////////////////////////////////////////////////////////////////////////
	bool Video::ParseReturn(HRESULT hret)
	{
		if (hret == S_OK)
			return false;

		return true;
	}

	LRESULT CALLBACK Video::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		auto video = (Video*)GetWindowLongPtr(hWnd, GWL_USERDATA);
		switch (message)
		{
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}