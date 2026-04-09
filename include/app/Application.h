#ifndef ARCADE_APP_APPLICATION_H
#define ARCADE_APP_APPLICATION_H

#include "app/GameManager.h"
#include "app/WindowConfig.h"

namespace arcade {

class Application {
  	public:
		Application();
		~Application();

    	void run();

	private:
		void initialize();
		void applyWindowConfig(const WindowConfig& config) const;
		void shutdown();

		bool initialized_ = false;
		GameManager gameManager_;
};

}

#endif
