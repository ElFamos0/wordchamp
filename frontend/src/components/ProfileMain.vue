<template>
  <div class="hello">
    <v-container>
        <v-form>
            <v-alert v-model="errorShown" dismissible>
                {{ errorMessage }}
            </v-alert>
            <h4 style="font-family: 'Roboto', sans-serif;"> Modification du profil </h4>
            <div class="large-12 medium-12 small-12 cell">
                <v-row class="my-1">
                  <v-col align="center" justify="center" sm="8">
                    <v-file-input prepend-icon="" chips label="Avatar" id="file" ref="file" v-on:change="gereEnvoi()"></v-file-input>
                  </v-col>
                  <v-col align="center" justify="center" sm="4">
                    <v-btn color="primary" v-if="file" v-on:click="envoiAvatar()" style="font-family: 'Roboto', sans-serif;">Envoyer</v-btn>
                  </v-col>
                </v-row>
            </div>

            <div class="large-12 medium-12 small-12 cell mt-4">
                <v-row class="my-1">
                    <v-col align="center" justify="center" sm="8">
                      <v-text-field v-model="new_username" :counter="25" label="Username" required></v-text-field>
                    </v-col>
                    <v-col align="center" justify="center" sm="4">
                        <v-btn color="primary" v-if="new_username" v-on:click="envoiUsername()" style="font-family: 'Roboto', sans-serif;">Envoyer</v-btn>
                    </v-col>
                </v-row>
            </div>
        </v-form>
    </v-container>
  </div>
</template>

<script>
import { mapGetters, useStore } from 'vuex';
import axiosAuth from '@/api/axios-auth';
import { useRoute } from 'vue-router';

export default {
  name: 'profile-main',
  data(){
      return {
        file: null,
        new_username: null,
        errorShown: false,
        errorMessage: null,
        $router: useRoute(),
        $store: useStore(),
      }
  },
  computed: {
    ...mapGetters('auth', {
      username: 'getUsername'
    })
  },
  methods: {
      envoiUsername: function(){
        let that = this;
        axiosAuth.post( '/profile_set/username', {"username":that.new_username}).then(function(response) {
          that.$store.dispatch('auth/changeUsername', response.data.new_username)
        }).catch(function(err) {
          that.errorMessage = err.response.data.error;
          that.errorShown = true;
          // console.log(that.errorMessage)
        });
      },
      envoiAvatar(){
        let formData = new FormData();
        let that = this;
        formData.append('file', this.file);
        axiosAuth.post( '/profile_set/avatar',formData,
          {
            headers: {
              'Content-Type': 'multipart/form-data'
            }
          }
        ).catch(function(err) {
          that.errorMessage = err.response.data.error;
          that.errorShown = true;
        }).then(function(){
          that.$router.go();
        })
      },
      gereEnvoi(){
        this.file = this.$refs.file.files[0];
      }
    }
};
</script>