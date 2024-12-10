import LZString from "./node_modules/lz-string/libs/lz-string.min.js";

enum CompressOption {
  INVALID_UTF16 = "INVALID_UTF16",
  VALID_UTF16 = "VALID_UTF16",
  BASE64 = "BASE64",
  URI = "URI",
  UINT8ARRAY = "UINT8ARRAY",
}

const hello_world = "Hello World !!!";

const all_ascii =
  " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

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

function get_file_info(
  test_name: string,
  value: string,
  option: CompressOption,
): string {
  let print_string = `${test_name}\n{`;

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

  if (option !== CompressOption.UINT8ARRAY) {
    for (let i = 0; i < result.length; ++i) {
      char_codes.push(result.charCodeAt(i));
    }

    print_string += new Uint16Array(char_codes).join(", ");
  } else {
    print_string += new Uint8Array(LZString.compressToUint8Array(value)).join(
      ", ",
    );
  }

  print_string += "}";

  return print_string;
}

if (import.meta.main) {
  const options: Set<string> = new Set<string>(Object.keys(CompressOption));

  const text_strings: Map<string, string> = new Map<string, string>();
  text_strings.set("hello world", hello_world);
  text_strings.set("all ascii", all_ascii);
  text_strings.set("temp json", JSON.stringify(temp_json));
  text_strings.set("temp json float", JSON.stringify(temp_json_float));

  options.forEach((option) => {
    const text: string[] = [];

    text_strings.forEach((test, test_name) =>
      text.push(
        get_file_info(
          test_name,
          test,
          CompressOption[option as keyof typeof CompressOption],
        ),
      )
    );

    Deno.writeTextFileSync(`${option}.txt`, text.join("\n\n"));
  });
}
