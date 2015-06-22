#include "uutVideo.h"
#include "application/uutWindow.h"
#include "uutTexture.h"
#include "uutShader.h"
#include "core/uutCore.h"
#include "uutVideoBuffer.h"
#include "uutRenderTarget.h"

namespace uut
{
	Video::Video()
		: _swapChain(0)
		, _device(0)
		, _context(0)
	{
	}

	bool Video::SetMode(const IntVector2& size, bool fullscreen)
	{
		_size = size;
		if (_window == nullptr)
		{
			_window = new Window();
			_window->Create(_size);
			GetCore()->AddModule(_window);
		}

		DXGI_SWAP_CHAIN_DESC scd;
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

		scd.BufferDesc.Width = _size.x;
		scd.BufferDesc.Height = _size.y;
		scd.BufferDesc.RefreshRate.Numerator = 60;
		scd.BufferDesc.RefreshRate.Denominator = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		scd.BufferCount = 1;                                    // one back buffer
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
		scd.OutputWindow = _window->GetHWND();
		scd.SampleDesc.Count = 4;
		scd.Windowed = fullscreen ? FALSE : TRUE;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		HRESULT hret = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE,
			NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &scd, &_swapChain, &_device, NULL, &_context);
		if (ParseReturn(hret))
			return false;

		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = 1.0f*_size.x;
		viewport.Height = 1.0f*_size.y;

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

		if (_device)
			_device->Release();
		if (_context)
			_context->Release();
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

	SharedPtr<RenderTarget> Video::CreateRenderTarget()
	{
		SharedPtr<RenderTarget> target(new RenderTarget(this));

		_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&target->_data);
		_device->CreateRenderTargetView(target->_data, NULL, &target->_view);

		return target;
	}

	SharedPtr<Shader> Video::CreateShaderFromMemory(const VertexDeclare* decl, uint8_t count, const char* code, int size /* = -1 */)
	{
		if (code == nullptr)
			return SharedPtr<Shader>::EMPTY;

		if (size < 0)
			size = strlen(code);
		if (code == 0)
			return SharedPtr<Shader>::EMPTY;

		ID3DBlob* error = NULL;

		SharedPtr<Shader> shader(new Shader(this));
		auto ret = D3DCompile(code, size, "memory", 0, 0, "VS", "vs_4_0", 0, 0, &shader->_vsBlob, &error);
		if (ParseReturn(ret))
		{
			if (error)
			{
				auto msg = (char*)error->GetBufferPointer();
				error->Release();
			}

			return SharedPtr<Shader>::EMPTY;
		}

		ret = _device->CreateVertexShader(shader->_vsBlob->GetBufferPointer(), shader->_vsBlob->GetBufferSize(), NULL, &shader->_vs);
		if (ParseReturn(ret))
			return SharedPtr<Shader>::EMPTY;

		ret = D3DCompile(code, size, "memory", 0, 0, "PS", "ps_4_0", 0, 0, &shader->_psBlob, 0);
		if (ParseReturn(ret))
			return SharedPtr<Shader>::EMPTY;

		ret = _device->CreatePixelShader(shader->_psBlob->GetBufferPointer(), shader->_psBlob->GetBufferSize(), NULL, &shader->_ps);
		if (ParseReturn(ret))
			return SharedPtr<Shader>::EMPTY;

		//////////////////////////////////////////////////////////////////////////
		static const char* semanticName[3] = { "POSITION", "COLOR", "TEXCOORDS" };

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

	SharedPtr<VideoBuffer> Video::CreateBuffer(BufferType type, BufferUsage usage, unsigned int size)
	{
		D3D11_USAGE convertUsage[2] = { D3D11_USAGE_DEFAULT, D3D11_USAGE_DYNAMIC };

		SharedPtr<VideoBuffer> buffer;
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));

		switch (type)
		{
		case BufferType::Vertex:
			buffer = new VideoBuffer(type, this);
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			break;

		case BufferType::Index:
			buffer = new VideoBuffer(type, this);
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			break;

		case BufferType::Constant:
			buffer = new VideoBuffer(type, this);
			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			break;

		default:
			return SharedPtr<VideoBuffer>::EMPTY;
		}

		bd.Usage = convertUsage[(int)usage];
		bd.ByteWidth = size;

		auto ret = _device->CreateBuffer(&bd, NULL, &buffer->_data);
		if (ParseReturn(ret))
			return SharedPtr<VideoBuffer>::EMPTY;

		return buffer;
	}

	bool Video::SetTarget(RenderTarget* target)
	{
		if (target == nullptr)
			return false;

		_context->OMSetRenderTargets(1, &target->_view, NULL);
		return true;
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

	bool Video::SetVertexBuffer(VideoBuffer* buffer, unsigned int stride, unsigned int offset)
	{
		if (buffer == nullptr || buffer->GetType() != BufferType::Vertex)
			return false;

		UINT _stride = stride;
		UINT _offset = offset;
		_context->IASetVertexBuffers(0, 1, &buffer->_data, &_stride, &_offset);
		return true;
	}

	bool Video::SetIndexBuffer(VideoBuffer* buffer, IndexType type, unsigned int offset)
	{
		static const DXGI_FORMAT convert[] = { DXGI_FORMAT_R16_UINT, DXGI_FORMAT_R32_UINT };

		if (buffer == nullptr || buffer->GetType() != BufferType::Index)
			return false;

		_context->IASetIndexBuffer(buffer->_data, convert[(int)type], offset);
		return true;
	}

	bool Video::SetConstantBuffer(VideoBuffer* buffer)
	{
		if (buffer == nullptr || buffer->GetType() != BufferType::Constant)
			return false;

		_context->VSSetConstantBuffers(0, 1, &buffer->_data);
		return true;
	}

	bool Video::SetTopology(VertexTopology topology)
	{
		static const D3D_PRIMITIVE_TOPOLOGY convert[] = {
			D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
			D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
			D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		};

		_context->IASetPrimitiveTopology(convert[(int)topology]);
		return true;
	}

	bool Video::Draw(unsigned int count, unsigned int start)
	{
		_context->Draw(count, start);
		return true;
	}

	bool Video::DrawIndexed(unsigned int count, unsigned int start, unsigned int baseVertex)
	{
		_context->DrawIndexed(count, start, baseVertex);
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
}