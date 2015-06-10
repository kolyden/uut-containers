#include "Video.h"
#include "Window.h"
#include "Texture.h"
#include "Shader.h"
#include "VideoBuffer.h"
#include "BufferLayout.h"

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
			_window = std::make_unique<Window>();
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
			NULL,
			NULL,
			NULL,
			D3D11_SDK_VERSION,
			&scd,
			&_swapChain,
			&_device,
			NULL,
			&_context);

		_backBuffer = std::make_shared<Texture>();
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

	std::shared_ptr<Shader> Video::CreateShaderFromMemory(const char* code, ShaderType type)
	{
		if (code == nullptr)
			return nullptr;

		ID3D10Blob* blob = nullptr;
		std::shared_ptr<Shader> shader;
		switch (type)
		{
		case ShaderType::Vertex:
			if (D3DX11CompileFromMemory(code, strlen(code), "shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &blob, 0, 0) == S_OK)
			{
				shader = std::make_shared<Shader>();
				if (_device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &shader->_vs) == S_OK)
				{
					shader->_blob = blob;
					shader->_type;
					return shader;
				}
			}
			break;

		case ShaderType::Pixel:
			if (D3DX11CompileFromMemory(code, strlen(code), "shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &blob, 0, 0) == S_OK)
			{
				shader = std::make_shared<Shader>();
				if (_device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &shader->_ps) == S_OK)
				{
					shader->_blob = blob;
					shader->_type;
					return shader;
				}
			}
			break;
		}

		return nullptr;
	}

	std::shared_ptr<Shader> Video::CreateShaderFromFile(const char* code, ShaderType type)
	{
		if (code == nullptr)
			return nullptr;

		ID3D10Blob* blob = nullptr;
		std::shared_ptr<Shader> shader;
		switch (type)
		{
		case ShaderType::Vertex:
			if (D3DX11CompileFromFile(code, 0, 0, "VShader", "vs_4_0", 0, 0, 0, &blob, 0, 0) == S_OK)
			{
				shader = std::make_shared<Shader>();
				if (_device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &shader->_vs) == S_OK)
				{
					shader->_blob = blob;
					shader->_type;
					return shader;
				}
			}
			break;

		case ShaderType::Pixel:
			if (D3DX11CompileFromFile(code, 0, 0, "PShader", "ps_4_0", 0, 0, 0, &blob, 0, 0) == S_OK)
			{
				shader = std::make_shared<Shader>();
				if (_device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &shader->_ps) == S_OK)
				{
					shader->_blob = blob;
					shader->_type;
					return shader;
				}
			}
			break;
		}

		return nullptr;
	}

	std::shared_ptr<VideoBuffer> Video::CreateBuffer(unsigned int size)
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = size;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		auto buffer = std::make_shared<VideoBuffer>();
		auto ret = _device->CreateBuffer(&bd, NULL, &buffer->_data);
		if (ParseReturn(ret))
			return nullptr;

		return buffer;
	}

	std::shared_ptr<BufferLayout> Video::CreateLayout(D3D11_INPUT_ELEMENT_DESC* desc, BYTE count, std::shared_ptr<Shader> shader)
	{
		auto layout = std::make_shared<BufferLayout>();
		auto ret = _device->CreateInputLayout(desc, count, shader->_blob->GetBufferPointer(), shader->_blob->GetBufferSize(), &layout->_layout);
		if (ParseReturn(ret))
			return nullptr;

		return layout;
	}

	bool Video::UpdateBuffer(std::shared_ptr<VideoBuffer> buffer, const void* ptr, unsigned int size)
	{
		if (!buffer)
			return false;

		D3D11_MAPPED_SUBRESOURCE ms;
		auto ret = _context->Map(buffer->_data, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
		if (ParseReturn(ret))
			return false;

		memcpy(ms.pData, ptr, size);
		_context->Unmap(buffer->_data, NULL);

		return true;
	}

	bool Video::SetShader(ShaderType type, std::shared_ptr<Shader> shader)
	{
		switch (type)
		{
		case ShaderType::Vertex:
			_context->VSSetShader(shader ? shader->_vs : nullptr, 0, 0);
			break;

		case ShaderType::Pixel:
			_context->PSSetShader(shader ? shader->_ps : nullptr, 0, 0);
			break;
		}

		return true;
	}

	bool Video::SetLayout(std::shared_ptr<BufferLayout> layout)
	{
		_context->IASetInputLayout(layout->_layout);
		return true;
	}

	bool Video::SetBuffer(std::shared_ptr<VideoBuffer> buffer, unsigned int stride, unsigned int offset)
	{
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