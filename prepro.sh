mkdir -p src
cp SUMMARY.md src/
cp -r General src/
cp -r Specifications src/
cp -r Tutorials src/

# mathjax
find src -type f -exec sed -i -e 's/$`/\\\\( /g' -e 's/`\$/ \\\\)/g' {} \;
