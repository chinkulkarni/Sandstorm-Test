pub unsafe auto trait DBSafe {}

// impl<T: Sized> !DBSafe for &T {}
// impl<T: Sized> !DBSafe for &mut T {}

impl<T: Sized> !DBSafe for *mut T {}
impl<T: Sized> !DBSafe for *const T {}
impl<T: Sized> !DBSafe for fn {}

pub fn parse<T: DBSafe + Sized>(test: T) -> T {
    return test;
}
