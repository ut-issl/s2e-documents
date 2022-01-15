mkdir -p src
cp SUMMARY.md src/
cp -r General src/
cp -r Specifications src/
cp -r Tutorials src/

# mathjax
find src -type f -exec sed -i -e 's/$`/\\\\( /g' -e 's/`\$/ \\\\)/g' {} \;
find src -type f -exec sed -i -z -e 's/```math\n\([^`]*\)```\n/\\\\[\n\1\\\\]\n/g' {} \;
