<?php

class Books{
	public $bid;
	public $title;
	public $author;
	public $nrPages;
	public $genre;
	public $borrowed;

	function __construct($bid, $title, $author, $nrPages, $genre, $borrowed){
		$this->bid = $bid;
		$this->title = $title;
		$this->author = $author;
		$this->nrPages = $nrPages;
		$this->genre = $genre;
		$this->borrowed = $borrowed;
	}

	function get_bid(){
		return $this->bid;
	}

	function set_bid($newID){
		$this->bid = $newID;
	}

	function get_title(){
		return $this->title;
	}

	function set_title($newTitle){
		$this->title = $newTitle;
	}

	function get_author(){
		return $this->author;
	}

	function set_author($newAuthor){
		$this->author = $newAuthor;
	}

	function get_nrPages(){
		return $this->nrPages;
	}

	function set_nrPages($newNrPages){
		$this->nrPages = $newNrPages;
	}

	function get_genre(){
		return $this->genre;
	}

	function set_genre($newGenre){
		$this->genre = $newGenre;
	}

	function get_borrowed(){
		return $this->borrowed;
	}

	function set_borrowed($newBorrowed){
		$this->borrowed = $newBorrowed;
	}
}

?>