```bash
sudo apt install doxygen
sudo apt install graphviz
cd docs
doxygen -g Doxyfile #generuje doxyfile, nie trzeba robić
doxygen
# otwórz docs/html/index.html
firefox html/index.html

```