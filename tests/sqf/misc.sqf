[   
   ["assertEqual",     { [1, 2, 3] apply {0x1} }, [1,1,1]],
   ["assertEqual",     { [] apply {+1} }, []],
   ["assertEqual",     { {_x > 1} count [1, 2, 3] }, 2],
   ["assertEqual",     { {_x > 1} count [] }, 0],
   ["assertEqual",     { [1, 2, 3] findIf {_x > 1} }, 1],
   ["assertEqual",     { [1, 2, 3] findIf {_x > 5} }, -1],
   ["assertEqual",     { [] findIf {_x > 1} }, -1],
   ["assertTrue",      { 1 >= 1 }],
   ["assertTrue",      { 1 <= 1 }],
   ["assertEqual",     { toLower "UPPER" }, "upper"],
   ["assertEqual",     { toUpper "lower" }, "LOWER"],
   ["assertEqual",     { format [] }, ""],
   ["assertEqual",     { format [true] }, ""],
   ["assertEqual",     { format ["%a"] }, ""],
   ["assertEqual",     { format ["%5"] }, ""],
   ["assertEqual",     { toArray "123" }, [49,50,51]],
   ["assertEqual",     { toString [49,50,51] }, "123"],
   ["assertEqual",     { ["1","2","3"] joinString "-"  }, "1-2-3"],
   ["assertEqual",     { [1,2,3] joinString "-"  }, "1-2-3"],
   ["assertEqual",     { "a"+"b"  }, "ab"],
   ["assertFalse",     { isNil {"a"+"b"}  }],
   ["assertEqual",     { for "_i" from 1 to 10 do { _i }; }, 10],
   //["assertEqual",     { for [{ _i = 0 }, { _i < 10 }, { _i = _i + 1 }] do { _i };  }, 10] //not implemented
   ["assertEqual",     { str (switch (true)) }, "true"]
   

]