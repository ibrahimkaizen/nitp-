/**
 * @file
 * JavaScript behaviors.
 */

(function ($) {
    Drupal.behaviors.nitp = {
        attach: function (context, settings) {
            let baseurl = "https://projectdemo.com.ng/nitp/";
            
            let q1 = document.getElementById("edit-field-are-you-returning-to-niger-und-1");
            if (q1) {
                q1.addEventListener('click', function(event){
                    $('#modal-default').modal('show');
                });
            }
            
            $('#edit-field-what-country-are-you-trave-und-205, #edit-field-what-country-are-you-trave-und-206, #edit-field-what-country-are-you-trave-und-207').each(function(){
                    $(this).on('click', function(){
                        $('#modal-country').modal('show');
                    })
            })
            
            $(".group-one .multipage-link-next").on('click', function(){
                let email = $("#edit-field-email-und-0-email").val()
                window.covid_form_email = email;
                if (email) {
                    $.ajax({
                        url: baseurl+"cvdform/save-toses",
                        type: "post",
                        data: {"email": email}
                    })
                }
                
            })
            
            $('.form-item-field-hotel-isolation-center-und').on('click', function(){
                    $('#modal-hotel').modal('show');
            })
            
            $('#sendvc', context).once().on('click', function(event){
               let phone = $("#edit-field-phone-number-und-0-value").val();
               if (phone && phone.length == 11) {
                   let email = $("#edit-field-email-und-0-email").val();
                    $.ajax({
                        url: baseurl+"cvdform/send-sms",
                        type: "post",
                        data: {"phone": phone, "email": email} ,
                        success: function (response) {
                            let msg = "Kindly enter the OTP sent to " + phone + " and " + email;
                            alert(msg);
                            //console.log(response)
                        },
                        error: function(jqXHR, textStatus, errorThrown) {
                           console.log(textStatus, errorThrown);
                        }
                    });
               }else {
                   alert('Invalid Phone Number. Phone number must have 11 characters without country code.')
               }
            });
        }
    }
}(jQuery));