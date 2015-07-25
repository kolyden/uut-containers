#include "uutGui.h"
#include "core/uutCore.h"
#include "input/uutInput.h"
#include "application/uutWindow.h"
#include "video/uutRender.h"
#include "video/uutTexture.h"
#include "video/uutVertexBuffer.h"
#include "video/uutIndexBuffer.h"
#include "video/uutVertexLayout.h"

namespace uut
{
	static int VERTEX_BUFFER_SIZE = 20000;
	static int INDEX_BUFFER_SIZE = 40000;

	static Gui* g_gui = nullptr;

	struct CUSTOMVERTEX
	{
		Vector3f pos;
		DWORD col;
		Vector2f uv;
	};

	const List<VertexDeclare> VERTEX_DECLARE = {
		{ DECLARE_POSITION, VALUE_FLOAT, 3, 0, 0 },
		{ DECLARE_COLOR, VALUE_DWORD, 1, offsetof(CUSTOMVERTEX, col), 0 },
		{ DECLARE_TEXCOORDS, VALUE_FLOAT, 2, offsetof(CUSTOMVERTEX, uv), 0 },
	};

	Gui::Gui()
	{
		g_gui = this;
	}

	void Gui::Update(float deltaTime)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = deltaTime;
		io.KeyCtrl = _input->IsKey(KEY_CONTROL);
		io.KeyShift = _input->IsKey(KEY_SHIFT);
		io.KeyAlt = _input->IsKey(KEY_MENU);

		RECT rect;
		GetClientRect((HWND)_window->GetHWND(), &rect);
		io.DisplaySize = ImVec2((float)(rect.right - rect.left), (float)(rect.bottom - rect.top));

		ImGui::NewFrame();
	}

	void Gui::Draw()
	{
		_render->SetRenderState(RenderState::Lightning, false);
		_render->SetRenderState(RenderState::ZEnable, false);
		_render->SetRenderState(RenderState::ScissorTest, true);
		_render->SetRenderState(RenderState::AlphaBlend, true);
		_render->SetRenderState(RenderState::AlphaTest, false);
		_render->SetBlendOp(BLENDOP_ADD);
		_render->SetCullMode(CULL_NONE);
		_render->SetBlendType(BlendType::Source, BLEND_SRCALPHA);
		_render->SetBlendType(BlendType::Dest, BLEND_INVSRCALPHA);

		_render->SetTextureOp(0, TSS_COLOROP, TEXOP_SELECTARG1);
		_render->SetTextureArgument(0, TSS_COLORARG1, TEXARG_DIFFUSE);
		_render->SetTextureOp(0, TSS_ALPHAOP, TEXOP_MODULATE);
		_render->SetTextureArgument(0, TSS_ALPHAARG1, TEXARG_TEXTURE);
		_render->SetTextureArgument(0, TSS_COLORARG2, TEXARG_DIFFUSE);

		_render->SetTextureFilter(0, TEXFILTERTARGET_MIN, TEXFILTER_LINEAR);
		_render->SetTextureFilter(0, TEXFILTERTARGET_MAG, TEXFILTER_LINEAR);

		ImGui::Render();

		_render->SetRenderState(RenderState::ScissorTest, false);
		_render->SetRenderState(RenderState::AlphaBlend, false);
		_render->SetRenderState(RenderState::ZEnable, true);
		_render->SetTextureOp(0, TSS_COLOROP, TEXOP_MODULATE);
		_render->SetTextureArgument(0, TSS_COLORARG1, TEXARG_TEXTURE);

		_render->SetCullMode(CULL_CCW);
	}

	//////////////////////////////////////////////////////////////////////////
	void Gui::OnInit()
	{
		_render = Core::GetMain()->GetModule<Render>();
		_window = Core::GetMain()->GetModule<Window>();
		_input = Core::GetMain()->GetModule<Input>();

		_window->AddEventListener(this);

		_vbuffer = _render->CreateVertexBuffer(USAGE_DYNAMIC, sizeof(CUSTOMVERTEX)* VERTEX_BUFFER_SIZE);
		_ibuffer = _render->CreateIndexBuffer(USAGE_DYNAMIC, sizeof(uint16_t)* INDEX_BUFFER_SIZE, INDEX_16);
		_layout = _render->CreateVertexLayout(VERTEX_DECLARE);

		ImGuiIO& io = ImGui::GetIO();
		io.KeyMap[ImGuiKey_Tab] = KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = KEY_PRIOR;
		io.KeyMap[ImGuiKey_PageDown] = KEY_NEXT;
		io.KeyMap[ImGuiKey_Home] = KEY_HOME;
		io.KeyMap[ImGuiKey_End] = KEY_END;
		io.KeyMap[ImGuiKey_Delete] = KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = KEY_BACK;
		io.KeyMap[ImGuiKey_Enter] = KEY_RETURN;
		io.KeyMap[ImGuiKey_Escape] = KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = KEY_A;
		io.KeyMap[ImGuiKey_C] = KEY_C;
		io.KeyMap[ImGuiKey_V] = KEY_V;
		io.KeyMap[ImGuiKey_X] = KEY_X;
		io.KeyMap[ImGuiKey_Y] = KEY_Y;
		io.KeyMap[ImGuiKey_Z] = KEY_Z;

		io.RenderDrawListsFn = &DrawListStatic;
		io.ImeWindowHandle = _window->GetHWND();

		io.DisplaySize = ImVec2(
			(float)_window->GetSize().x,
			(float)_window->GetSize().y);

		// Build
		unsigned char* pixels;
		int width, height, bytes_per_pixel;
		io.Fonts->GetTexDataAsAlpha8(&pixels, &width, &height, &bytes_per_pixel);

		_texture = _render->CreateTexture(Vector2i(width, height), FORMAT_A8);
		if (_texture == nullptr)
		{
			IM_ASSERT(0);
			return;
		}

		auto tex_locked_rect = _texture->Lock();
		if (tex_locked_rect._bits == nullptr)
		{
			IM_ASSERT(0);
			return;
		}
		for (int y = 0; y < height; y++)
			memcpy((unsigned char *)tex_locked_rect._bits + tex_locked_rect._pitch * y, pixels + (width * bytes_per_pixel) * y, (width * bytes_per_pixel));
		_texture->Unlock();

		// Store our identifier
		io.Fonts->TexID = (void*)_texture;

		// Cleanup (don't clear the input data if you want to append new fonts later)
		io.Fonts->ClearInputData();
		io.Fonts->ClearTexData();

		ImGui::NewFrame();
	}

	void Gui::OnDone()
	{
		_window->RemoveEventListener(this);
	}

	void Gui::OnKeyDown(EKeycode code)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[code] = true;
	}

	void Gui::OnKeyUp(EKeycode code)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[code] = false;
	}

	void Gui::OnChar(uint32_t c)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(c);
	}

	void Gui::OnMouseDown(int button)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[button] = true;
	}

	void Gui::OnMouseUp(int button)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[button] = false;
	}

	void Gui::OnMouseMove(const Vector2i& pos)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos.x = 1.0f * pos.x;
		io.MousePos.y = 1.0f * pos.y;
	}

	void Gui::OnMouseWheel(float delta)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel = delta;
	}

	void Gui::DrawList(ImDrawData* draw_data)
	{
		auto vtx_dst = (CUSTOMVERTEX*)_vbuffer->Lock(0, draw_data->TotalVtxCount * sizeof(CUSTOMVERTEX), true);
		if (vtx_dst == nullptr)
			return;

		auto idx_dst = (ImDrawIdx*)_ibuffer->Lock(0, draw_data->TotalIdxCount * sizeof(ImDrawIdx), true);
		if (idx_dst == nullptr)
			return;

		for (int n = 0; n < draw_data->CmdListsCount; n++)
		{
			const ImDrawList* cmd_list = draw_data->CmdLists[n];
			const ImDrawVert* vtx_src = &cmd_list->VtxBuffer[0];
			for (int i = 0; i < cmd_list->VtxBuffer.size(); i++)
			{
				vtx_dst->pos.x = vtx_src->pos.x;
				vtx_dst->pos.y = vtx_src->pos.y;
				vtx_dst->pos.z = 0.0f;
				vtx_dst->col = (vtx_src->col & 0xFF00FF00) | ((vtx_src->col & 0xFF0000) >> 16) | ((vtx_src->col & 0xFF) << 16);     // RGBA --> ARGB for DirectX9
				vtx_dst->uv.x = vtx_src->uv.x;
				vtx_dst->uv.y = vtx_src->uv.y;
				vtx_dst++;
				vtx_src++;
			}
			memcpy(idx_dst, &cmd_list->IdxBuffer[0], cmd_list->IdxBuffer.size() * sizeof(ImDrawIdx));
			idx_dst += cmd_list->IdxBuffer.size();
		}
		_vbuffer->Unlock();
		_ibuffer->Unlock();
		_render->SetVertexBuffer(0, _vbuffer, 0, sizeof(CUSTOMVERTEX));
		_render->SetIndexBuffer(_ibuffer);
		_render->SetVertexLayout(_layout);

		// Setup render state: fixed-pipeline, alpha-blending, no face culling, no depth testing

		// Setup orthographic projection matrix
		_render->SetTransform(TransformType::World, Matrix4::IDENTITY);
		_render->SetTransform(TransformType::View, Matrix4::IDENTITY);

		D3DXMATRIXA16 mat;
		D3DXMatrixOrthoOffCenterLH(&mat, 0.5f, ImGui::GetIO().DisplaySize.x + 0.5f, ImGui::GetIO().DisplaySize.y + 0.5f, 0.5f, -1.0f, +1.0f);
		_render->GetDevice()->SetTransform(D3DTS_PROJECTION, &mat);

		// Render command lists
		int vtx_offset = 0;
		int idx_offset = 0;
		for (int n = 0; n < draw_data->CmdListsCount; n++)
		{
			const ImDrawList* cmd_list = draw_data->CmdLists[n];
			for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); cmd_i++)
			{
				const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
				if (pcmd->UserCallback)
				{
					pcmd->UserCallback(cmd_list, pcmd);
				}
				else
				{
					const Recti r(
						(LONG)pcmd->ClipRect.x, (LONG)pcmd->ClipRect.y,
						(LONG)pcmd->ClipRect.z - (LONG)pcmd->ClipRect.x,
						(LONG)pcmd->ClipRect.w - (LONG)pcmd->ClipRect.y);

					_render->SetTexture(0, (Texture*)pcmd->TextureId);
					_render->SetScissorRect(&r);
					_render->DrawIndexedPrimitive(PRIMITIVE_TRIANGLELIST,
						vtx_offset, 0, cmd_list->VtxBuffer.size(),
						idx_offset, pcmd->ElemCount / 3);
				}
				idx_offset += pcmd->ElemCount;
			}
			vtx_offset += cmd_list->VtxBuffer.size();
		}
	}

	void Gui::DrawListStatic(ImDrawData* draw_data)
	{
		g_gui->DrawList(draw_data);
	}
}