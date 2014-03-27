jEditable inline editing module


Installation:

1. Place this module in your favorite modules directory (i.e., sites/all/modules/)
2. Download the jEditable jQuery plugin from http://www.appelsiini.net/download/jquery.jeditable.mini.js
     If you're in *nix and in the module directory, you can use this:
     wget http://www.appelsiini.net/download/jquery.jeditable.mini.js
3. Enable the module
     If you're at the command line, then hopefully you have drush you can use:
     drush en jeditable
4. Turn on the "use jeditable" permission for all rolls you want to have access to jeditable operations.
     The module respects basic node access, so saving using jeditable will only work if the user has "update" permissions on the node.
     However, if they don't have update permissions, they will still get the jeditable input forms, so this needs some thought for your application.
5. Go to the "display settings" of your node, or into the display settings for a view with fields in it and
     enable the jEditable textfield, jEditable textarea, jEditable datetime or jEditable noderefence fields as appropriate
6. Finally, load a node, "click to edit", and enjoy!



Instructions for Workflow integration

If you have the workflow module, you can use jeditable to change workflow statuses. It won't show up anywhere
by default, but you can place it in .tpl.php files by using the following theme function:

theme('jeditable_workflow', $node);

You can also use the computed_field module to get this to show up as a field in views and elsewhere. Use
the following snippets.

For "Computed Code":
$node_field[0]['value'] = workflow_get_state_name($node->workflow);

For "Display format":
$display = theme('jeditable_workflow', $element['#node']);

For Data type, select "varchar" and set data length to 60 (or whatever you set as maximum length for workflow state names)

What this will do is store the workflow state name in the database so that you can use this in views and sort by state name.
What is then displayed is themed jeditable select drop down.