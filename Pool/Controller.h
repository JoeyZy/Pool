#include "Model.h"
#include "View.h"

class Controller {
	Model *model;
	View view;
public:
	Controller();
	~Controller();
	void setModel(Model *model) {
		this->model = model;
	}
	Model* getModel(){
		return model;
	}
	void setView(View view) {
		this->view = view;
	}
	View getView(){
		return view;
	}
};