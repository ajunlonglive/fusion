#FuRouter
- Dynamic ReGex problem char set:
  "::foo(@bar_)" = 'underscore problem', is removed after parsed to FUSION_STORE session.
  "::foo(' ' ')" = 'single tick', is need it to escaped using backslash " \' ". Or if not, will parsed as exec code.
- "cd function = issues when print with concat => procedure test: cd $i."<br />";
- adding support for internal framework error to work with PhpErrorHandler
- empty placeholder e.g. "Route::get("/:")" is can be allowed [bug]