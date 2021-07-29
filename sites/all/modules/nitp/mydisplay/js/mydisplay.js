/**
 * @file
 * JavaScript behaviors.
 */

 (function ($) {
    
    Drupal.behaviors.mydisplay = {
      attach: function (context, settings) {
          let base = "https://projectdemo.com.ng/nitp/"
    
          $(".form-item-field-laboratory-nitp-und select", context).once().on('change', function(){
              let id = $(this).val()
              if(id) {
                $.ajax({
                  url: base+"dspl/lab/"+id,
                  success: function(response){
                    let arrival_date = $("#edit-field-arrival-date2 input").val();
                    var dateParts = arrival_date.split("/");
                    let date = new Date(new Date(+dateParts[2], dateParts[1] - 1, +dateParts[0]))
                    date.setDate(date.getDate() + 7)
    
                    let content = `<p><strong>Lab Address: </strong> ${response.address}</p><p><strong> Contact Number: </strong> ${response.phone}</p><p><strong> Appointment Date: </strong>${date}</p>`
                    $("#lab-detail").html(
                      "<div class='lab-info well'>"+ content +"</div>"
                    )
                  }
                })
              } else {
                $("#lab-detail").html()
              }
              
          });
          
          $("#edit-field-preferred-currency input", context).once().on('change', function(){
              let currency = $(this).val()
              let tids = []
              let names = []
              $(".form-item-field-laboratory-nitp-und select option").each(function(){
                let val = $(this).val()
                if (val !== '_none') {
                  tids.push(val)
                }
              })
              
              $.ajax({
                url: `${base}dspl/currency/${currency}`,
                method: 'POST',
                data: {tids: tids},
                success: function(response){
                  $(".form-item-field-laboratory-nitp-und select option").each(function(index, element){
                    let val = $(this).val()
                    if (val !== '_none') {
                        let name = $(this).text()
                        let name_arr = name.split("|");
                        $(this).text(`${name_arr[0]} | ${response.amounts[index]}`)
                    }
                  })
                }
              })
          });
    
          $("#edit-field-country-of-first-departur2 select", context).once().on('change', function(event){
            let id = $(this).val()
            let bits = Drupal.settings.nitpjs.bit_keys;
            if (bits.includes(id)) {
                $("#myModal").modal('show');
            }
          });
          
          $("#edit-field-mode-of-payment input", context).once().on('change', function(event){
            if ($(this).val() == 1){
                $("#modeofpaymentmodal").modal('show');
            }
          });
          
          
          
          
          
          $("#edit-field-confirm-passport-number-und-0-value", context).once().on('keyup change', function(event){
              if ($(this).val() != $("#edit-field-passport-number-und-0-value").val()){
                  $(this).attr('aria-invalid', true);
                  $(".field-name-field-confirm-passport-number .mydescription").html("<span class='text-danger error'>Passport number field not equal</span>")
              }else {
                  $(".field-name-field-confirm-passport-number .mydescription").html("")
              }
          });
          
          $("#edit-field-email2-und-0-email", context).once().on('keyup change', function(event){
              if ($(this).val() != $("#edit-field-email-und-0-email").val()){
                  $(this).attr('aria-invalid', true);
                  $(".form-item-field-email2-und-0-email .mydescription").html("<span class='text-danger error'>Email field not equal</span>")
              }else {
                  $(".form-item-field-email2-und-0-email .mydescription").html("")
              }
          });
   
          
          let accordion = $('div.field-group-accordion-wrapper');
          
          $(".mygroup-prev", context).once().on('click', function () {
                let pregroup = $(this).data('nextid');
                accordion.accordion("option", "active", pregroup);
                
          });
          
          
          
          $(".mygroup-next", context).once().on('click', function () {
                let nextgroup = $(this).data('nextid');
                let current = nextgroup - 1;
                let id = `#ui-accordion-1-panel-${current} select`;
                let allfilled = [];
                $(id).filter('.required').each(function(){
                    let val = $(this).val();
                    if (val === '_none') {
                        allfilled.push(false);
                    }
                })
                
                let good;
                
                if (allfilled.length === 0){
                    good = true
                }else {
                    good = allfilled.every(e => e === true);
                }
                
                if ($('select, input, textarea', this.wrapper).valid()) {
                    if (nextgroup - 1 === 0 ) {
                        let email = $("#edit-field-email-und-0-email").val();
                        let confirmemail = $("#edit-field-email2-und-0-email").val();
                        let passport = $("#edit-field-passport-number-und-0-value").val();
                        let confirmpassport = $("#edit-field-confirm-passport-number-und-0-value").val();
                        
                        let cp = (confirmpassport) ? confirmpassport : passport;
                        
                        
                        if (email === confirmemail && passport === cp && good) {
                            accordion.accordion("option", "active", nextgroup);
                        }else {
                            if (email != confirmemail) {
                                $(".form-item-field-email2-und-0-email .mydescription").html("<span class='text-danger error'>Email field not equal</span>");
                            }
                            if (passport != confirmpassport) {
                                $(".field-name-field-confirm-passport-number .mydescription").html("<span class='text-danger error'>Passport number field not equal</span>");
                            }
                        }
                        
                    }else {
                        if (good){
                         accordion.accordion("option", "active", nextgroup);
                        }
                    }
                   
                }
          });
          
          $(".mygroup-submit", context).once().on('click', function () {
                $([document.documentElement, document.body]).animate({
                    scrollTop: $("#edit-preview").offset().top
                }, 2000);
          
          });
 
          
          
          /**$(".field-group-format-toggler a").each(function(){
              let text = $(this).text();
              let name_arr = text.split("|");
              $(this).html(`<span class="mygroup-numbering">${name_arr[0]}</span> ${name_arr[1]}`);
          });**/
          
      }
    }
}(jQuery));