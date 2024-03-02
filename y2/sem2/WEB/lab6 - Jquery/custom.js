$(document).ready(function() {
  $('body').append('<div class="tabs"></div>');
  $.each([1,2,3,4,5],function(index,value){
    $('.tabs').append('<div class="tab-link" data-tab="tab'+ value +'">Tab' + value + '</div>');
  });

  $.each(["rain","forest","ocean","stars","clouds"],function(index,value){
    let nr = index + 1
    $('body').append('<div id="tab' + nr + '" class="tab-content">');
    $('#tab' + nr).append('<h2>' + value + '</h2>');
    $('#tab' + nr).append('<img src="' + value + '1.png" alt="image1">');
    $('#tab' + nr).append('<img src="' + value + '2.png" alt="image2">');
    $.each([1,2,3], function(index2, value2){
        $('#tab' + nr).append('<div>Div ' + nr + '.' + value2 + '</div>');
    });
  });

  // Set CSS
  $('.tabs').css({'display': 'flex', 'justify-content': 'center', 'align-items': 'center', 'margin-top': '20px'});
  $('.tab-link').css({'padding': '10px', 'margin-right': '10px', 'border': '1px solid #ccc', 'border-radius': '5px 5px 0 0', 'background-color': '#8daa9d', 'cursor': 'pointer'});
  $('.tab-content').css({'padding': '20px', 'border': '1px solid #ccc', 'border-top': 'none', 'background-color': '#fbf5f3'});
  $('.tab-content img').css({'padding-right': '10px'});
  
  // Hide all tab content on page load
  $('.tab-content').hide();

  // Show the first tab content on page load
  $('.tab-content:first').show();

  // Add active class to first tab link on page load
  $('.tab-link:first').addClass('active').css({
    'background-color': '#fbf5f3', 
    'border-bottom': 'none'});

  // Click function for tab links
  $('.tab-link').click(function() {
    // Remove active class from all tab links
    $('.tab-link').removeClass('active').css({
      'padding': '10px', 'margin-right': '10px', 
      'border': '1px solid #ccc', 
      'border-radius': '5px 5px 0 0', 
      'background-color': '#8daa9d', 
      'cursor': 'pointer'});

    // Add active class to clicked tab link
    $(this).addClass('active').css({
      'background-color': '#fbf5f3', 
      'border-bottom': 'none'});

    // Hide all tab content
    $('.tab-content').hide();

    // Get the id of the clicked tab link and show the corresponding tab content
    var tabContentId = $(this).attr('data-tab');
    $('#' + tabContentId).show();
  });
});
