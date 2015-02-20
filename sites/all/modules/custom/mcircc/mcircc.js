jQuery(document).ready(function($) {

    // Add commas after user titles and departments in a field collection.
    // Struggled with theming an individual field within a field collection, so
    // we cheaped out and used jQuery to save the day.
    var selector =
      'body.page-members .views-field-field-user-positions .field-name-field-title .field-item, ' +
      'body.page-user .views-field-field-user-positions .field-name-field-title .field-item, ' +
      'body.page-members .views-field-field-user-positions .field-name-field-department .field-item, ' +
      'body.page-user .views-field-field-user-positions .field-name-field-department .field-item ';
      /*'body.page-members .views-field-field-user-positions .field:not(:last-child)' +
      'body.page-user .views-field-field-user-positions .field:not(:last-child)';*/
    $.each($(selector), function(index, object) {
        //$(object).children('.field-items .field-item').append(',');
        $(object).append(',');
    });

    // We're using field_user_research_interests in an interesting way, in that
    // there may often be text entered for the item, but no URL. If there is no
    // URL we want to hide the text. The link module doesn't have any field
    // formatters to accomplish this, and we're lazy and don't want to write a
    // custom field formatter. So we'll use jQuery to remove any items that
    // don't have a URL. If we end up removing both, then hide the "research
    // interests field label too."
    var items = $('body.page-user .views-field-field-user-research-interests ul li');
    var removed = 0;
    $.each(items, function(index, item) {
        if ($(item).children('a').length == 0) {
          $(item).remove();
          removed++;
        }
    });
    if (removed && items.length == removed) {
      $('body.page-user .views-field-field-user-research-interests').hide();
    }
    
});
