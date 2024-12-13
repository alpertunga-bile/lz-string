import LZString from "./node_modules/lz-string/libs/lz-string.min.js";

const data_folder: string = "../test_src/data";

enum CompressOption {
  INVALID_UTF16 = "INVALID_UTF16",
  VALID_UTF16 = "VALID_UTF16",
  BASE64 = "BASE64",
  URI = "URI",
  UINT8ARRAY = "UINT8ARRAY",
}

function convert_to_Uint8Array(data: string): Uint8Array {
  const is_odd = data.charCodeAt(data.length - 1) % 256 === 0;

  const buffer = new Uint8Array(data.length * 2 - (is_odd ? 1 : 0));

  for (let i = 0; i < data.length; ++i) {
    const current_value = data.charCodeAt(i);

    buffer[i * 2] = current_value >>> 8;

    if (!is_odd || i < data.length - 1) {
      buffer[i * 2 + 1] = current_value % 256;
    }
  }

  return buffer;
}

function convert_from_Uint8Array(data: Uint8Array): string {
  const length = Math.floor(data.byteLength / 2);
  const arr = [];

  for (let i = 0; i < length; ++i) {
    arr.push(String.fromCharCode(data[i * 2] * 256 + data[i * 2 + 1]));
  }

  if (data.byteLength & 1) {
    arr.push(String.fromCharCode(data[data.byteLength - 1] * 256));
  }

  return arr.join("");
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

function write_result(
  test_name: string,
  value: string,
  option: CompressOption,
) {
  const char_codes: number[] = [];
  const test_folder = `${data_folder}/${test_name}`;

  try {
    Deno.mkdirSync(test_folder);
  } catch (error) {
  }

  Deno.writeTextFileSync(`${test_folder}/data.bin`, value);

  const test_filepath = `${test_folder}/${
    CompressOption[option].toLowerCase()
  }.bin`;

  let result: string | Uint8Array;

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
    case CompressOption.UINT8ARRAY:
      result = new Uint8Array(LZString.compressToUint8Array(value));

      Deno.writeFileSync(
        test_filepath,
        result,
      );
      return;
  }

  if (
    option === CompressOption.BASE64 ||
    option === CompressOption.URI
  ) {
    for (let i = 0; i < result.length; ++i) {
      char_codes.push(result.charCodeAt(i));
    }

    Deno.writeFileSync(
      test_filepath,
      new Uint8Array(char_codes),
    );

    return;
  }

  const converted = convert_to_Uint8Array(result);
  Deno.writeFileSync(test_filepath, converted);
}

if (import.meta.main) {
  const options: Set<string> = new Set<string>(Object.keys(CompressOption));

  const text_strings: Map<string, string> = new Map<string, string>();

  text_strings.set("hello_world", hello_world);
  text_strings.set("all_ascii", all_ascii);
  text_strings.set("temp_json", JSON.stringify(temp_json));
  text_strings.set("temp_json_float", JSON.stringify(temp_json_float));
  text_strings.set(
    "repeated",
    "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccdddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd",
  );
  text_strings.set(
    "pi",
    Deno.readTextFileSync(`${data_folder}/pi.bin`),
  );
  text_strings.set(
    "lorem_ipsum",
    Deno.readTextFileSync(`${data_folder}/lorem_ipsum.bin`),
  );
  text_strings.set(
    "tattoo",
    Deno.readTextFileSync(`${data_folder}/tattoo.bin`),
  );

  options.forEach((option) => {
    text_strings.forEach((test, test_name) =>
      write_result(
        test_name,
        test,
        CompressOption[option as keyof typeof CompressOption],
      )
    );
  });
}
