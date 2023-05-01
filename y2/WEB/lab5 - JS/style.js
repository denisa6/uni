window.onload = function() {

  for(var i = 1; i < 6; i++){
    var node = document.createElement('li');
    node.appendChild(document.createTextNode('Menu Item ' + i));
    var sublist = document.createElement('ul');
    sublist.setAttribute('class', 'submenu');
    for(var j = 1; j < 6; j++){
        sublistElem = document.createElement('li');
        sublistElem.appendChild(document.createTextNode('Submenu Item ' + i + '.' + j))
        sublist.appendChild(sublistElem)
    }
    node.appendChild(sublist);
    document.querySelector('ul').appendChild(node);
  }

  var menuItems = document.querySelectorAll(".menu li");
  for (var i = 0; i < menuItems.length; i++) {
    menuItems[i].addEventListener("click", toggleSubmenu);
  }
};
    
function toggleSubmenu() {
  var submenu = this.querySelector(".submenu");
  if (submenu.style.display === "block") {
    submenu.style.display = "none";
    this.classList.remove("active");
  } 
  else {
    submenu.style.display = "block";
    this.classList.add("active");
  }
}