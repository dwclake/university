let rec from_decimal = (~result=[], decimal: int, ~into: int): string => {
  switch decimal {
    | 0 => 
      List.fold_right( (++), result, "" )
    | _ =>
      let quotient = decimal / into;
      let rem = ( decimal mod into )
        |> Int.to_string;

      let result = [ rem, ...result ];
      
      from_decimal( quotient, ~into, ~result )
  }
};

let () = {
  let decimal = int_of_string @@ Sys.argv[1];
  let base = int_of_string @@ Sys.argv[2];

  print_endline @@ from_decimal( decimal, ~into=base )
};
