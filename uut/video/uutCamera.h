#pragma once
#include "uutVideoObject.h"

namespace uut
{

	inline DirectX::XMVECTOR GMathFV(XMFLOAT3& val)
	{
		return XMLoadFloat3(&val);
	}

	inline DirectX::XMFLOAT3 GMathVF(XMVECTOR& vec)
	{
		XMFLOAT3 val;
		XMStoreFloat3(&val, vec);
		return val;
	}

	inline XMMATRIX GMathFM(XMFLOAT4X4& val)
	{
		return XMLoadFloat4x4(&val);
	}

	inline XMFLOAT4X4 GMathMF(XMMATRIX& matrix)
	{
		XMFLOAT4X4 val;
		XMStoreFloat4x4(&val, matrix);
		return val;
	}

	class Camera
	{
	public:
		// Constructs default camera looking at 0,0,0
		// placed at 0,0,-1 with up vector 0,1,0 (note that mUp is NOT a vector - it's vector's end)
		Camera(void);
		// Create camera, based on another one
		Camera(const Camera& camera);
		// Copy all camera's parameters
		Camera& operator=(const Camera& camera);
		~Camera(void) {}

	private:
		// Initialize camera's View matrix from mPosition, mTarget and mUp coordinates
		void initViewMatrix();

	public:
		// Initialize camera's perspective Projection matrix
		void InitProjMatrix(const float angle, const float client_width, const float client_height,
			const float nearest, const float farthest);
		// Initialize camera's orthogonal projection
		void InitOrthoMatrix(const float client_width, const float client_height,
			const float near_plane, const float far_plane);

		// Resize matrices when window size changes
		void OnResize(uint32_t new_width, uint32_t new_height);

		///////////////////////////////////////////////
		/*** View matrix transformation interfaces ***/
		///////////////////////////////////////////////

		// Move camera
		void Move(XMFLOAT3 direction);
		// Rotate camera around `axis` by `degrees`. Camera's position is a 
		// pivot point of rotation, so it doesn't change
		void Rotate(XMFLOAT3 axis, float degrees);
		// Set camera position coordinates
		void Position(XMFLOAT3& new_position);
		// Get camera position coordinates
		const XMFLOAT3& Position() const { return mPosition; }
		// Change camera target position
		void Target(XMFLOAT3 new_target);
		// Get camera's target position coordinates
		const XMFLOAT3& Target() const { return mTarget; }
		// Get camera's up vector
		const XMFLOAT3 Up() { return GMathVF(GMathFV(mUp) - GMathFV(mPosition)); }
		// Get camera's look at target vector
		const XMFLOAT3 LookAtTarget() { return GMathVF(GMathFV(mTarget) - GMathFV(mPosition)); }
		// Returns transposed camera's View matrix      
		const XMFLOAT4X4 View() { return GMathMF(XMMatrixTranspose(GMathFM(mView))); }

		/////////////////////////////////////////////////////
		/*** Projection matrix transformation interfaces ***/
		/////////////////////////////////////////////////////

		// Set view frustum's angle
		void Angle(float angle);
		// Get view frustum's angle
		const float& Angle() const { return mAngle; }

		// Set nearest culling plane distance from view frustum's projection plane
		void NearestPlane(float nearest);
		// Set farthest culling plane distance from view frustum's projection plane
		void FarthestPlane(float farthest);

		// Returns transposed camera's Projection matrix
		const XMFLOAT4X4 Proj() { return GMathMF(XMMatrixTranspose(GMathFM(mProj))); }
		// Returns transposed orthogonal camera matrix
		const XMFLOAT4X4 Ortho() { return GMathMF(XMMatrixTranspose(GMathFM(mOrtho))); }

	private:
		/*** Camera parameters ***/
		XMFLOAT3 mPosition;         // Camera's coordinates
		XMFLOAT3 mTarget;           // View target's coordinates
		XMFLOAT3 mUp;                       // Camera's up vector end coordinates

		/*** Projection parameters ***/
		float mAngle;                   // Angle of view frustum
		float mClientWidth;             // Window's width
		float mClientHeight;    // Window's height
		float mNearest;                 // Nearest view frustum plane
		float mFarthest;                // Farthest view frustum plane

		XMFLOAT4X4 mView;          // View matrix
		XMFLOAT4X4 mProj;          // Projection matrix
		XMFLOAT4X4 mOrtho;         // Ortho matrix for drawing without tranformation
	};
}