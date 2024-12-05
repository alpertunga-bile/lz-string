import LZString from "./node_modules/lz-string/libs/lz-string.min.js";

// Learn more at https://docs.deno.com/runtime/manual/examples/module_metadata#concepts
if (import.meta.main) {
  console.log(LZString.compress("zxcasdqweqweqsad"));
}
