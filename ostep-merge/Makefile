VENV_DIR := .venv
PYTHON := $(VENV_DIR)/bin/python
PIP := $(VENV_DIR)/bin/pip
REQUIREMENTS := requirements.txt
TARGET := merge-ostep

.PHONY: all venv install clean run $(TARGET)

all: $(TARGET)

$(TARGET): venv install
	@echo "Generating executable..."
	@echo "#!$(PYTHON)" > $(TARGET)
	@cat merge-ostep.py >> $(TARGET)
	@chmod +x $(TARGET)
	@echo "Executable $(TARGET) created."

venv:
	@echo "Creating virtual environment..."
	@python3 -m venv $(VENV_DIR)
	@echo "Virtual environment created in $(VENV_DIR)"

install: venv
	@echo "Installing dependencies..."
	@$(PIP) install -r $(REQUIREMENTS)
	@echo "Dependencies installed."

run : install
	@echo "Running the application..."
	@./$(TARGET)
	@echo "Application finished."

clean:
	@echo "Cleaning up..."
	@rm -rf $(VENV_DIR)
	@rm if $(TARGET)
	@echo "Virtual environment removed."