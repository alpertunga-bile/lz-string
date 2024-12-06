import LZString from "./node_modules/lz-string/libs/lz-string.min.js";

enum CompressOption {
  INVALID_UTF16,
  VALID_UTF16,
  BASE64,
  URI,
}

const temp_json = {
  string: "Hello, World!",
  number: 123,
  boolean: true,
  null: null,
  array: [1, 2, 3, 4, 5],
  object: {
    name: "John Doe",
    age: 30,
    occupation: "Software Developer",
  },
  nested_object: {
    address: {
      street: "123 Main St",
      city: "Anytown",
      state: "CA",
      zip: "12345",
    },
  },
  array_of_objects: [
    {
      name: "Jane Doe",
      age: 25,
    },
    {
      name: "Bob Smith",
      age: 40,
    },
  ],
};

const temp_json_float = {
  float: 3.14159,
  double: 2.71828,
  negativeFloat: -0.12345,
  exponentialFloat: 1.23e-4,
  arrayOfFloats: [1.1, 2.2, 3.3, 4.4, 5.5],
  objectWithFloats: {
    pi: 3.14159,
    e: 2.71828,
  },
  nestedObjectWithFloats: {
    point: {
      x: 1.1,
      y: 2.2,
    },
  },
};

function write_char_code_arrays(value: string, option: CompressOption): void {
  let print_string = `{`;

  const char_codes: number[] = [];
  let result: string = "";

  switch (option) {
    case CompressOption.INVALID_UTF16:
      result = LZString.compress(value);
      break;
    case CompressOption.VALID_UTF16:
      result = LZString.compressToUTF16(value);
      break;
    case CompressOption.BASE64:
      result = LZString.compressToBase64(value);
      break;
    case CompressOption.URI:
      result = LZString.compressToEncodedURIComponent(value);
      break;
  }

  for (let i = 0; i < result.length; ++i) {
    char_codes.push(result.charCodeAt(i));
  }

  print_string += char_codes.join(", ");

  print_string += "}";

  Deno.writeTextFileSync("result.txt", print_string);
}

// Learn more at https://docs.deno.com/runtime/manual/examples/module_metadata#concepts
if (import.meta.main) {
  write_char_code_arrays(
    JSON.stringify(temp_json_float),
    CompressOption.INVALID_UTF16,
  );
}
