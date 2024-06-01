import { getAPI } from "./shared.js";

const indentString = (str, count, indent = "  ") =>
  str.replace(/^/gm, indent.repeat(count));

function handleArgs(args) {
  return Object.keys(args)
    .map((a) => `${a}: ${args[a]}`)
    .join(", ");
}

const api = await getAPI();

for (const cat of Object.keys(api)) {
  console.log(`interface ${cat} {`);
  const iface = [];
  for (const func of Object.keys(api[cat])) {
    const { returns, args, description } = api[cat][func];
    iface.push(
      indentString(
        `// ${description}\n${func.replace(/_/g, "-")}: func(${handleArgs(args)}) -> ${returns};`,
        1,
      ),
    );
  }
  console.log(iface.join("\n\n"));
  console.log("}\n");
}

console.log(`default world null0 {
${indentString(
  Object.keys(api)
    .map((cat) => `import ${cat};`)
    .join("\n"),
  1,
)}
}`);
