APP_NAME=subtee-server
APP_VOLUME="$(shell pwd):/app"

PORTS="5000:5000"

# Help
.PHONY: help
help: ## This help.
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

.DEFAULT_GOAL := help

DOCKER_RUN_CMD=docker run -i -t --rm --name=$(APP_NAME) -p=$(PORTS) -v=$(APP_VOLUME) $(APP_NAME)

build: ## Build the container
	docker build -t $(APP_NAME) .

install: ## Initialize development environment
	docker build -t $(APP_NAME) .
	$(DOCKER_RUN_CMD) pip install -r requirements.txt

run: ## Run Server
	$(DOCKER_RUN_CMD) python app.py

shell: ## Creates a bash inside the container
	$(DOCKER_RUN_CMD) bash
