import { Component, OnInit } from '@angular/core';
import {GenericService} from '../generic.service';
import {ActivatedRoute, Router} from '@angular/router';

@Component({
  selector: 'app-delete-book',
  templateUrl: './delete-book.component.html',
  styleUrls: ['./delete-book.component.css']
})
export class DeleteBookComponent implements OnInit{
	constructor(private service: GenericService, private router: Router, private route: ActivatedRoute) {
  	}

  	ngOnInit(): void {
  	}

  	onYes(): void {
    	this.service.deleteBook(this.route.snapshot.queryParams['id']).subscribe(() => {
      		this.router.navigate(['showBooks']).then(_ => {
      		});
    	});
  	}

  	onNo(): void {
    	this.router.navigate(['showBooks']).then(_ => {
    	});
  	}
}
