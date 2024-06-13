#[link(name = "ffi", kind = "static")]
extern "C" {
    pub fn hello_from_c(i: i32) -> i32;
}

fn main() {
    unsafe {
        let i = hello_from_c(666);
        println!("Hello World! says C: {}", i);
    }
}
