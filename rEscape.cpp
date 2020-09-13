#include <bangtal.h>
using namespace bangtal;

int main()
{
	auto scene2 = Scene::create("룸2", "images/background5.jpg");
	auto scene1 = Scene::create("룸1", "images/background4.jpg");
	auto scene3 = Scene::create("룸3", "images/background7.png");

	auto open1 = false;
	auto moved = false;
	auto open = false;
	auto appear1 = false;
	auto appear2 = false;
	auto locked = true;
	auto lighted = true;
	auto show = true;
	auto back = false;


	//scene2 구성
	auto ground = Object::create("images/ground1.jpg", scene2, 0, -350);
	ground->setScale(2.0f);

	auto key = Object::create("images/key1.jpg", scene2, 900, 205);
	key->setScale(0.3f);
	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		key->pick();
		return true;
		});

	auto plant = Object::create("images/plant.jpg", scene2, 800, 205);
	plant->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (moved == false) {
			if (action == MouseAction::MOUSE_DRAG_UP) {
				plant->locate(scene2, 800, 405);
				moved = true;
			}
		}
		return true;
	});

	auto door3 = Object::create("images/door7.jpg", scene2, 250, 205);
	door3->setScale(1.5f);
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (open1 == true) {
			scene1->enter();
		}
		else if (key->isHanded()) {
			door3->setImage("images/door8.jpg");
			open1 = true;
		}
		else {
			showMessage("열쇠가 필요해요~");
		}
		return true;
	});

	auto desk1 = Object::create("images/desk2.png", scene2, 550, 150);
	desk1->setScale(1.6f);


	//scene1 구성
	auto door1 = Object::create("images/door3.jpg", scene1, 350, 235);
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();
		return true;
	});

	auto door2 = Object::create("images/door3.jpg", scene1, 770, 235);

	auto h = Object::create("images/h3.jpg", scene1, 830, 325);
	h->setScale(0.1f);
	h->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene3->enter();
		return true;
	});

	auto mirror1 = Object::create("images/mirror1.jpg",scene1,420,100);
	mirror1->setScale(0.8f);
	mirror1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (appear1 == false) {
			auto h = Object::create("images/h3.jpg", scene1, 460, 170);
			h->setScale(0.35f);
			appear1 = true;
		}
		return true;
	});

	auto mirror2 = Object::create("images/mirror1.jpg", scene1, 630, 100);
	mirror2->setScale(0.8f);
	mirror2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (appear2 == false) {
			auto windows = Object::create("images/windows.jpg", scene1, 660, 170);
			windows->setScale(0.35f);
			appear2 = true;
		}
		return true;
	});

	auto window1 = Object::create("images/window1.jpg",scene1,530,400);
	window1->setScale(0.8f);
	window1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (locked) {
			showMessage("문이 잠겨 있어요~");
		}
		else if (open == true) {
			endGame();
		}
		else {
			window1->setImage("images/window2.jpg");
			open = true;
		}
		return true;
	});

	window1->setOnKeypadCallback([&](ObjectPtr object)->bool {
		locked = false;
		showMessage("철커덕~");
		return true;
	});

	auto keypad = Object::create("images/keypad2.jpg", scene1, 700, 380);
	keypad->setScale(0.1f);
	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("windows", window1);
		return true;
	});

	auto hint1 = Object::create("images/hint1.png", scene1, 950, 500, false);
	hint1->setScale(0.5f);

	auto button = Object::create("images/button.jpg", scene1, 200, 400);
	button->setScale(0.2f);
	button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (lighted) {
			hint1->show();
			scene1->setLight(0.2f);
			lighted = false;
		}
		else {
			hint1->hide();
			scene1->setLight(1.0f);
			lighted = true;
		}
		return true;
	});


	//scene3 구성
	auto hint2 = Object::create("images/hint2.png", scene3, 150, 400, false);

	auto message = Object::create("images/message.png", scene3, 200, 200);

	auto angel = Object::create("images/angel.png", scene3, 900, 600);
	angel->setScale(0.1f);
	angel->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (show) {
			hint2->show();
			scene3->setLight(0.2f);
			show = false;
		}
		else {
			hint2->hide();
			scene3->setLight(1.0f);
			show = true;
		}
		return true;
	});

	auto devil = Object::create("images/devil.png", scene3, 500, 400);
	devil->setScale(0.5f);
	devil->setOnKeypadCallback([&](ObjectPtr object)->bool {
		back = true;
		devil->setImage("images/angel.png");
		angel->hide();
		message->hide();
		showMessage("나와 함께 돌아가요~");
		return true;
	});

	devil->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (back == true) {
			scene1->enter();
		}
		else {
			showMessage("암호를 외치면 돌아갈 수 있어요~");
			showKeypad("505", devil);
		}
		return true;
	});

	

	startGame(scene2);
}
