%for($array as $key => $elem)
    %for($i = 0; $i < 12; $i++)
    %for($array as $key => $elem)
    %efor
    %efor
%efor
%for($i = 0; $i < 12; $i++)
    %for($array as $key => $elem)

    %for($i = 0; $i < 12; $i++)
    %efor
        {{ $elem | safe_html }}
    %efor
||%efor

{{ $test | unsafe_html }}|