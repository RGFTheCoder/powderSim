#include <vector>
#include <memory>
#include "Sketch/Sketch.hh"
#include "Cell/Cell.hh"
#include "Cell/CellWorld.hh"

#include "Cell/Cells/Cells.hh"

class Automata : public Sketch
{
protected:
	CellWorld data;

	RenderTexture2D target;
	u32 scl = 10;

	void Setup() override
	{
		windowName = "Automata";
		fps = 60;
		resetWindow();
		target = LoadRenderTexture(screenWidth - 20, screenHeight - (20 + 5 * 10));

		BeginTextureMode(target);
		ClearBackground(WHITE);
		EndTextureMode();
	};

	template <class T, typename std::enable_if<std::is_base_of<Cell, T>::value>::type * = nullptr>
	void AddParticle(u32 x, u32 y)
	{
		T *powder = new T(data, x, y);
		if (!powder->gFlags.valid)
			delete powder;
	}

	void Update() override
	{
		AddParticle<Powder>(5, 39 - 1);
		AddParticle<Water>(34, 39 - 1);
		data.UpdateWorld();
	};
	void Draw() override
	{
		ClearBackground({100, 120, 255});
		BeginTextureMode(target);
		for (auto pos : data.changes)
		{
			auto res = data.pos(pos.x, pos.y);
			if (res.success)
			{
				Cell *cell = res.value;
				if (cell == nullptr)
					DrawRectangle(pos.x * scl, pos.y * scl, scl, scl, {0xff, 0xff, 0xff, 0xff});
				else
					DrawRectangle(pos.x * scl, pos.y * scl, scl, scl, cell->Draw());
			}
		}
		while (data.changes.size() > 0)
			data.changes.pop_back();
		EndTextureMode();
		DrawTextureRec(target.texture, (Rectangle){0, 0, (float)target.texture.width, (float)target.texture.height}, (Vector2){10, 10}, WHITE);
	};

	void Unload() override
	{
		UnloadRenderTexture(target);
	}
};
static Automata *sk = new Automata;

int main()
{
	return *sk;
}