#pragma once
#include "layer.h"

class appLayer : public Layer
{
	public:
	virtual ~appLayer() = default;
	virtual void OnUpdate(float ts) override;
	virtual void OnRender() override;
};

