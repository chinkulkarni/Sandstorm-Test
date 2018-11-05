#![feature(optin_builtin_traits)]

mod safe;

use std::sync::RwLock;

use safe::parse;

struct Test {
    a: fn() -> (),
    b: u64,
}

fn hi() {}

fn test() {
    let test  = Test { a: hi, b: 0 };
    parse(test);
}
