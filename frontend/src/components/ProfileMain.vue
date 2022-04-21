<template>
  <div class="hello">
    <b-container>
        <b-form-group>
            <b-alert v-model="errorMessage" variant="danger" dismissible>
                {{ errorMessage }}
            </b-alert>

            <div class="large-12 medium-12 small-12 cell">
                <label>Avatar : 
                    <input type="file" id="file" ref="file" v-on:change="gereEnvoi()"/>
                </label>
                <b-button variant="primary" v-if="file" v-on:click="envoiAvatar()">Envoyer</b-button>
            </div>

            <div class="large-12 medium-12 small-12 cell mt-4">
                <b-row class="my-1">
                    <b-col sm="2">
                        <label for="input-small">Username:</label>
                    </b-col>
                    <b-col sm="8">
                        <b-form-input id="input-small" size="sm" v-model="new_username" v-bind:placeholder="username"></b-form-input>
                    </b-col>
                    <b-col sm="2">
                        <b-button variant="primary" v-if="new_username" v-on:click="envoiUsername()">Envoyer</b-button>
                    </b-col>
                </b-row>
            </div>
        </b-form-group>
    </b-container>
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
          console.log(that.errorMessage)
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